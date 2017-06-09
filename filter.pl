#!/usr/bin/perl

@l = ("Number of Threads", "INTEGER INDEX", "FLOATING-POINT INDEX", "MEMORY INDEX", "OVERALL INDEX");
while(<>)
{
    $line = $_;
    foreach(@l) {
        if ($line=~/^$_\s*:\s*(\d.*?)\s*$/)
        {
            print $1, "\n";
            last;
        }
    }
}
