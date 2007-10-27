#!@RCD_SCRIPTS_SHELL@
#
# $NetBSD: dbmailtimsieved.sh,v 1.2 2007/10/27 15:35:43 obache Exp $
#

# PROVIDE: dbmailtimsieved mail
# REQUIRE: 

. /etc/rc.subr

name="dbmailtimsieved"
rcvar=${name}
required_files="@PKG_SYSCONFDIR@/dbmail.conf"
command="@PREFIX@/sbin/dbmail-timsieved"
pidfile="@VARBASE@/run/dbmail-timsieved.pid"

load_rc_config $name
run_rc_command "$1"
