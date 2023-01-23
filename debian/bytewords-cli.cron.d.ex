#
# Regular cron jobs for the bytewords-cli package.
#
0 4	* * *	root	[ -x /usr/bin/bytewords-cli_maintenance ] && /usr/bin/bytewords-cli_maintenance
