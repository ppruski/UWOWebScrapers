#!/usr/bin/perl -w

use strict;

use LWP;

use feature 'say';
use pQuery;


chomp(my $firstParam=$ARGV[0]);
chomp(my $secondParam=$ARGV[1]);
my $query = $firstParam . "." . $secondParam;

my $site = 'http://www.uwo.ca/cgi-bin/dsgw/whois2html2';

my $req = HTTP::Request->new(POST => $site);
$req->content_type('application/x-www-form-urlencoded');
$req->content('server=localhost&query=' . $query);

my $http = LWP::UserAgent->new();
my $res = $http->request($req);
if ($res->is_success) {
	my $body = $res->content;
	printf STDOUT ("POST to %s successful.\n", $site);

	pQuery( $body )
		->find( "pre" )->each(
			sub {

			my $n = shift;
			my $pQ = pQuery( $_ ); 

			my $isProblem=$pQ->text;
			#my $firstChars = substr($isError, 0, 5);
			if ($isProblem =~ m/Error/) {
				printf STDOUT ( "More than 250 results found.\n" );
				exit 13;
			} elsif ($isProblem =~ m/No matches/) {
				printf STDOUT ( "No matches found\n" );
				exit 7;	
			} else {
				say $pQ->text;
			}

			}
		);

} else {
	printf STDERR ("ERROR: Cannot POST to %s (Code: %d)\n", $site, $res->code);
}

