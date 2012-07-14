#!/usr/bin/perl
# Output a version.c file that includes information about the current build
# Adapted from existing mkversion.pl script for svn now named mksvnversion.pl

# Clear environment locale so that git will not use localized strings
$ENV{'LC_ALL'} = "C";
$ENV{'LANG'} = "C";

my $gitversion = 0;
my $present = 0;
my $clean = 2;
my @compiletime = gmtime();

# Call git log and extract last changed revision
if(open(GITLOG, "git log -n 1 |")) {
	while(<GITLOG>) {
		if (/^commit (.*)/) {
			$present = 1;
			$clean = 1;
			$gitversion = $1;
			## last; # Do not abort here, since SVN tends to complain about a Broken pipe
		}
	}
	close(GITLOG);
}

$compiletime[4] += 1;
$compiletime[5] += 1900;
my $ctime = sprintf("%6\$04i/%5\$02i/%4\$02i %3\$02i:%2\$02i:%1\$02i", @compiletime);
$gitversion = substr($gitversion, 0, 10);

print <<EOF
#include "proxmark3.h"
/* Generated file, do not edit */
const struct version_information __attribute__((section(".version_information"))) version_information = {
	VERSION_INFORMATION_MAGIC,
	1,
	$present,
	$clean,
	"git $gitversion",
	"$ctime",
};
EOF
