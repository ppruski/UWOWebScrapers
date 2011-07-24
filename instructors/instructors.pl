#!/usr/bin/perl -w

use strict;
use warnings;

use URI;
use LWP;

use feature 'say';
use pQuery;
use Data::Dumper::Simple;
use Web::Scraper;
use LWP::UserAgent;
use LWP::Simple;


use lib "lib";
use YAML;

chomp(my $firstname=$ARGV[0]);
chomp(my $lastname=$ARGV[1]);

my $site = 'http://www.uwo.ca/cgi-bin/dsgw/people.pl';

my $req = HTTP::Request->new(POST => $site);
$req->content_type('application/x-www-form-urlencoded');
$req->content('mode=general_search&firstname=' . $firstname . '&lastname=' . $lastname . '&info=Starts+with');

my $http = LWP::UserAgent->new();
my $res = $http->request($req);
if ($res->is_success) {
	my $body = $res->content;
	printf STDOUT ("POST to %s successful.\n", $site);

	# First, create your scraper block
	my $profs = scraper {
		process '//html/body/p[5]/table//tr', 'profs[]' => scraper {
			process '//tr//td[1]/font/a', 'name' => 'TEXT';
			process '//tr//td[2]/font/a', 'email' => 'TEXT';
			process '//tr//td[3]/font/a', 'dept' => 'TEXT';
		};
	};

	printf STDOUT ("Search --- First name: " . $firstname . " ; Last name: " . $lastname . "\n");

	my $res = $profs->scrape( $body );
{
	no warnings 'uninitialized';

        for my $prof (@{$res->{profs}}) {
                print "$prof->{name}:$prof->{email}:$prof->{dept} \n";
        }
}


} else {
	printf STDERR ("ERROR: Cannot POST to %s (Code: %d)\n", $site, $res->code);
}

