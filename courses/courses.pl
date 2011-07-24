#!/usr/bin/perl -w

use strict;
use warnings;

use URI;
use LWP;

use feature 'say';
use pQuery;
use Data::Dumper::Simple;
use Web::Scraper;

chomp(my $subject=$ARGV[0]);
#chomp(my $secondParam=$ARGV[1]);

my $site = 'https://studentservices.uwo.ca/secure/Timetables/mastertt/tt1.cfm';

my $req = HTTP::Request->new(POST => $site);
$req->content_type('application/x-www-form-urlencoded');
$req->content('subject=' . $subject . '&Designation=Any&catalognbr=&CourseTime=All&Status=All&Component=All&time=&day=&Submit2=Search+Timetable');

my $http = LWP::UserAgent->new();
my $res = $http->request($req);
if ($res->is_success) {
	my $body = $res->content;
	printf STDOUT ("POST to %s successful.\n", $site);
#	print $body;

	# First, create your scraper block
	my $profs = scraper {
			#change this
		process "//html/body/p", "profs[]" => scraper {
			process "//font/b", "course" => 'TEXT';
		        process "//table[2]//tr/td[8]/font", "instructor" => 'TEXT';
		};
	};

	my $res = $profs->scrape( $body );

	for my $prof (@{$res->{profs}}) {
		print "$prof->{course}$prof->{instructor}\n";
	}

#	foreach (@$res) {
#	      print "$_\n";
#	}

} else {
	printf STDERR ("ERROR: Cannot POST to %s (Code: %d)\n", $site, $res->code);
}

