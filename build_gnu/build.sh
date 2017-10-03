#!/bin/bash

print_usage () {
    # Display usage and exit

    me=`basename $0`
    cat <<EOF
$me [options] <job parameters>

Where [options] is one or more of:
   -h           Print this usage and return
   -v           Increase verbose level (default=1)
   +v           Decrease verbose level
   -V <file>    Redirect progress to file <file>
   -E <file>    Same as -V but also sends an email with EMAILCMD
   -j <N>       Set number of parallel jobs for \make\

   -s <steps>   Explicity list of execution steps
   -i <dir>     Install base directory, default: /opt/freescale                
   -I           Install style: <dir>/<prefix> (default: <dir>/<prefix>/<host>)
   -r           Remove object directories after build
   -FSF         Report results to FSF list

Where <job parameters> is one or more of:
   <descriptor>   Job descriptor to execute
   s=<source set> Set source descriptor to use
   p=<patch set>  List of patches to use
   t=<descriptor> A dejagnu descritor to use for tests
   u=<user>       A username to be used on remote connections
   T=<>           Run an individual test e.g: "-v tree-prof.exp=val-prof*"
   rev=<num>      Do the build with subversion revision number <num>

And <steps> is one or more of:
   chk           Check version of required packages
   dst           Remove all of the working directory
   rm            Remove installation directory
   src           Get source from repository (if not present)
   intgr         Integrate libraries sources into gcc sources (gmp, mpfr, ppl, cloog, mpc)
   Xbin          Build cross binutils
   Nbin          Build native binutils
   NbinS         Build native binutils with sysroot
   gccM          Build minimum gcc w/o headers for linux
   EgccM         Build minimum gcc w/o headers for eabi
   lhdr          Build linux headers
   ghdr          Build glibc headers (multilib)
   gccS          Build minimum gcc with sysroot
   glibc         Build glibc (multilib)
   Xloc          Build cross locale
   Nloc          Build native locale
   Gloc          Complete Glibc locale and finish installation
   Xgcc          Build final gcc for linux
   Egcc          Build final gcc for eabi
   Ngcc          Build native gcc
   newlib        Build newlib
   newlib_nano   Build NewLib nano
   Nglibc        Build native glibc
   spec          Fix spec file
   link          Create soft links without exec-prefix
   Tbin          Run dejagnu binutils tests
   Tgcc          Run dejagnu gcc tests
   Tglibc        Run dejagnu glibc tests
   tar           Create a release tarball
   RelNotes      Generate release notes from texi
EOF
    exit 0
}

build_exit () {
    # Function to do some bookeeping before real exit

    if [ "$argEMAIL" = "Y" ]; then
	cp -f $argVERBFILE $REPODIR/logs/emailfile.txt
	eval $EMAILCMD
	rm -f $REPODIR/logs/emailfile.txt
    fi

    exit $1
}

parse_args () {
    # Function to parse all optional arguments

    # The arguments affects the following env vars:
    argVERBFILE=""
    argEMAIL="N"
    cmdLSTSTEPS=""
    argINSTSTYLE="H"
    argKEEP="Y"
    argFSF="N"

    # Whatever is not parsed is returned in env var:
    local idx

    idx=0
    while [ $# -ne 0 ]; do
	a=$1
	shift
	case $a in
	    -h)
		print_usage
		;;
	    -v)
		let argVERB=$argVERB+1
		;;
	    +v)
		let argVERB=$argVERB-1
		if [ $argVERB -lt 0 ]; then argVERB=0; fi
		;;
	    -V)
		argVERBFILE=$REPODIR/logs/$1; shift
		mkdir -p $REPODIR/logs
		;;
	    -E)
		argVERBFILE=$REPODIR/logs/$1; shift
		mkdir -p $REPODIR/logs
		argEMAIL="Y"
		;;
	    -j)
		NJOBS="-j $1"; shift
		;;
	    -s)
		cmdLSTSTEPS="$cmdLSTSTEPS $1"; shift
		;;
	    -i)
		TOOLINSTBASE="$1"; shift
		;;
	    -I)
		argINSTSTYLE="N"
		;;
	    -r)
		argKEEP="N"
		;;
	    -FSF)
		argFSF="Y"
		;;
	    *)
		PARAM[$idx]=$a
		idx=$idx+1
		;;
	esac
    done
}

echoV () {
    # Function to echo messages according to verbose level

    # Arguments are:
    # Desired verbose level
    local VERB=$1
    shift

    # This function is affected by the env var:
    # argVERB
    # argPRGFILE

    if [ $VERB -le $argVERB ]; then
	if [ "$argVERBFILE" = "" ]; then
	    echo "$@"
	else
	    echo "$@" >> $argVERBFILE
	fi
    fi
}

check_numargs () {
    # Function to validate the number of arguments of any other function

    # Arguments are
    # Name of the function being validated
    local FUNC=$1
    shift
    # Desired number of args
    local N=$1
    shift
    # Actual number of args
    local NARGS=$1
    shift

    if [ $N -gt $NARGS ]; then
	echoV 0 "[check_numargs] Invalid number of arguments for \"$FUNC\" expected $N got $NARGS"
	build_exit 1
    fi
}

untar_any () {
    # Function to untar any file format

    # Arguments are:
    local tar=$1

    local b btgz bgz bz2 btar bxz btxz

    check_numargs untar_any 1 $# $@

    b=`basename $tar`
    btgz=`basename $b .tgz`
    bgz=`basename $b .gz`
    bz2=`basename $b .bz2`
    btar=`basename $b .tar`
    bxz=`basename $b .xz`
    btxz=`basename $b .txz`

    echoV 1 -n "   Exploding: $tar   "
    if [ "$b" != "$btgz" -o "$b" != "$bgz" ];then
	echoV 3 "$tar is a gzip file name"
	tar xzfs $tar
	if [ $? != 0 ]; then echoV 1 "...Error"; return; else echoV 1 "...Ok"; fi
    elif [ "$b" != "$bz2" ]; then
	echoV 3 "$tar is a bzip2 file name"
	tar xjfs $tar
	if [ $? != 0 ]; then echoV 1 "...Error"; return; else echoV 1 "...Ok"; fi
    elif [ "$b" != "$btar" ]; then
	echoV 3 "$tar is an uncompressed tarfile"
	tar xfs $tar
	if [ $? != 0 ]; then echoV 1 "...Error"; return; else echoV 1 "...Ok"; fi
    elif [ "$b" != "$btxz" -o "$b" != "$xz" ];then
	echoV 3 "$tar is a xz file name"
	tar xJfs $tar
	if [ $? != 0 ]; then echoV 1 "...Error"; return; else echoV 1 "...Ok"; fi
    else
	echoV 0 "[untar_any] Unrecognized file format: $tar"
	build_exit 1
    fi
}

test_copylibs () {
    # Function to copy gcc / glibc to a remote board for testing w/ dyn libs

    # Argumets are:
    # Sequence for log file numbering
    local LN=$1
    # Dir of installed libs
    local HOSTDIR=$2
    # Multilib index
    local m=$3
    # Unique suffix
    local sfx=$4

    check_numargs test_copylibs 4 $# $@

    local i type libdir host usr

    type=${dBRDTYPE}
    host=${dBRDHOSTNAME}
    usr=$USER
    libdir=${dBRDLIBDIR}_$sfx

    echoV 2 -e "\ttype=$type \n\thost=$host \n\tusr=$usr"
    echoV 2 -e "\tm=$m "

    case $type in
	nat*)
	    return
	    ;;
	none)
	    return
	    ;;
	remote)
	    echoV 1 -n -e "   Removing gcc libs and glibc sysroot         "
	    ssh -l $usr $host "rm -rf $libdir/lib $libdir/lib64 \
		$libdir/libc" > $LOGFILE.$LN.test_setup 2>&1
	    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return
	    else echoV 1 "...Ok"; fi

	    echoV 1 -n -e "   Copying new gcc libs to target board        "
	    ssh -l $usr $host "mkdir -p $libdir" \
		>> $LOGFILE.$LN.test_setup 2>&1
	    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return; fi
	    scp -r $HOSTDIR/lib ${usr}@${host}:$libdir/lib \
		>> $LOGFILE.$LN.test_setup 2>&1
	    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return
	    else echoV 1 "...Ok"; fi

	    if [ -d $HOSTDIR/lib64 ]; then
		echoV 1 -n -e "   Copying new gcc libs to target board        "
		scp -r $HOSTDIR/lib64 ${usr}@${host}:$libdir/lib64 \
		    >> $LOGFILE.$LN.test_setup 2>&1
		if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return
		else echoV 1 "...Ok"; fi
	    fi

	    echoV 1 -n -e "   Copying new glibc sysroot to target board   "
	    scp -r $HOSTDIR/libc ${usr}@${host}:$libdir/libc \
		>> $LOGFILE.$LN.test_setup 2>&1
	    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return
	    else echoV 1 "...Ok"; fi
	    ;;
	*)
	    echoV 0 "[test_copylibs] Invalid type for dBRDTYPE type=$type"
	    build_exit 1
	    ;;
    esac
}

test_remlibs () {
    # Function to remove gcc / glibc from a remote board

    # Argumets are:
    # Sequence for log file numbering
    local LN=$1
    # Multilib index
    local m=$2
    # Unique suffix
    local sfx=$3

    check_numargs test_remlibs 3 $# $@

    local i type libdir host usr x f

    type=${dBRDTYPE}
    host=${dBRDHOSTNAME}
    usr=$USER
    libdir=${dBRDLIBDIR}_$sfx

    echoV 2 -e "\ttype=$type \n\thost=$host \n\tusr=$usr"
    echoV 2 -e "\tm=$m "

    case $type in
	nat*)
	    return
	    ;;
	none)
	    return
	    ;;
	remote)
	    echoV 1 -n -e "   Removing gcc libs and glibc sysroot         "
	    ssh -l $usr $host "rm -rf $libdir" \
		> $LOGFILE.$LN.test_cleanup 2>&1
	    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return; else echoV 1 "...Ok"; fi
	    # Collect the name of all files that need to be deleted
	    x=`find . -name rm_files`
	    rm -f all_rm_files
	    for f in $x; do
		cat $f >> all_rm_files
		rm -f $f
	    done
	    x=$RANDOM
	    echoV 1 -n -e "   Send list of files to be removed            "
	    scp -q all_rm_files $usr@$host:/tmp/all_rm_files_$x \
		>> $LOGFILE.$LN.test_cleanup 2>&1
	    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return; else echoV 1 "...Ok"; fi
	    echoV 1 -n -e "   Execute xargs on the list                   "
	    ssh -l $usr $host "cat /tmp/all_rm_files_$x | xargs rm -f" \
		>> $LOGFILE.$LN.test_cleanup 2>&1
	    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return; else echoV 1 "...Ok"; fi
	    echoV 1 -n -e "   Remove the list                             "
	    ssh -l $usr $host "rm -f /tmp/all_rm_files_$x" \
		>> $LOGFILE.$LN.test_cleanup 2>&1
	    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return; else echoV 1 "...Ok"; fi
	    ;;
	*)
	    echoV 0 "[test_remlibs] Invalid type for dBRDTYPE type=$type"
	    build_exit 1
	    ;;
    esac
}

test_fixboard () {
    # Function to replace REPODIR and DYNLNK on dejagnu boards

    # Arguments are:
    # board name
    local bname=$1
    # A suffix to name the modified file
    local sfx=$2
    # multilib directory
    local mlosdir=$3
    # Gcc libraries directory
    local gccdir=$4
    # Glibc libraries directory
    local libdir=$5
    # Original install directory
    local instdir=$6
    # multib directory (second part)
    local mldir=$7
    
    check_numargs test_fixboard 7 $# $@

    local dynlnk

    # First build strings to be replaced
    echoV 2 "Trying to find dynamic linker in $instdir"
    if [ -e $instdir/lib64/ld-linux-x86-64.so.2 ]; then
	# x86_64
	dynlnk="$libdir/lib64/ld-linux-x86-64.so.2,-rpath,$libdir/lib64,-rpath,$gccdir/lib64 \
            -L$libdir/lib64 -L$gccdir/lib64"
    elif [ -e $instdir/lib/ld.so.1 -a "$mlosdir" != "../lib64" ]; then
	# ppc 32
	dynlnk="$libdir/$mldir/lib/ld.so.1,-rpath,$libdir/$mldir/lib,-rpath,$gccdir/lib/$mldir \
	    -L$libdir/$mldir/lib -L$gccdir/lib/$mldir"
    elif [ -e $instdir/lib/ld-linux.so.2 ]; then
	# i686
	dynlnk="$libdir/lib/ld-linux.so.2,-rpath,$libdir/lib,-rpath,$gccdir/lib \
	    -L$libdir/lib -L$gccdir/lib"
    elif [ -e $instdir/lib64/ld64.so.1 -a "$mlosdir" = "../lib64" ]; then
	# ppc 64
	dynlnk="$libdir/lib64/ld64.so.1,-rpath,$libdir/lib64,-rpath,$gccdir/lib64 \
	    -L$libdir/lib64 -L$gccdir/lib64"
    else
	echoV 0 "[test_fixboard] Cannot find dynamic linker"
	build_exit 1
    fi

    if [ "$dUSESYS" = "Y" ]; then
	dynlnk="$dynlnk --sysroot=$INSTLIBDIR"
    else
	dynlnk="$dynlnk --sysroot=$instdir"
    fi

    echoV 1 -n -e "   Customizing dejagnu board file              "
    sed "s;REPODIR;$REPODIR;g" < $REPODIR/build_gnu/boards/${bname}.exp \
	| sed "s;DYNLNK;$dynlnk;g" \
	| sed "s:USER:$USER:g" > $REPODIR/build_gnu/boards/${bname}${sfx}.exp
    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return
    else echoV 1 "...Ok"; fi
}

test_fixboard_eabi () {
    # Function to replace REPODIR and DYNLNK on dejagnu boards

    # Arguments are:
    # board name
    local bname=$1
    # A suffix to name the modified file
    local sfx=$2
    # Gcc libraries directory
    local gccdir=$3
    # Glibc libraries directory
    local libdir=$4
    # Original install directory
    local instdir=$5
    
    check_numargs test_fixboard_eabi 5 $# $@

    echoV 1 -n -e "   Customizing dejagnu board file              "
    sed "s;REPODIR;$REPODIR;g" < $REPODIR/build_gnu/boards/${bname}.exp \
	| sed "s:USER:$USER:g" > $REPODIR/build_gnu/boards/${bname}${sfx}.exp
    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return
    else echoV 1 "...Ok"; fi
}

test_savelogs () {
    # Function to save dejagnu log files

    # Argumets are:
    # Sequence for log file numbering
    local LN=$1
    shift
    # List of files to save

    local f b

    for f in $@; do
	if [ -f $f ]; then
	    b=`basename $f`
	    cp -f $f $LOGFILE.$LN.$b
	fi
    done
}

test_FSFreport () {
    # Function to report results to FSF

    # Argumets are:
    # Sequence for log file numbering
    local LN=$1

    if [ "$argFSF" = "Y" ]; then
	../src_gcc/contrib/test_summary > $LOGFILE.$LN.FSFreport 2>&1
        ../src_gcc/contrib/test_summary | sh
    fi
}

split_version () {
    # Function to split version number into VER[]

    # Arguments are:
    local v=$1

    if [ "$v" = "" ]; then
	# No version given
	VER=(0 0 0 0 0 0)
	NVER=0
    else
	VER=(`echo $v | tr "." " "`)
	if [ "${VER[0]}" != "0" -a "${VER[0]}" != "1" -a "${VER[0]}" != "2" \
	    -a "${VER[0]}" != "3" -a "${VER[0]}" != "4" -a "${VER[0]}" != "5" \
	    -a "${VER[0]}" != "6" -a "${VER[0]}" != "7" -a "${VER[0]}" != "8" \
	    -a "${VER[0]}" != "9" ]; then
	    NVER=0
	elif [ "${VER[1]}" = "" ]; then
	    NVER=1
	elif [ "${VER[2]}" = "" ]; then
	    NVER=2
	elif [ "${VER[3]}" = "" ]; then
	    NVER=3
	elif [ "${VER[4]}" = "" ]; then
	    NVER=4
	else
	    NVER=5
	fi
    fi
    VER[0]=`echo ${VER[0]} | awk '{printf ("%d",$1); exit}'`
    VER[1]=`echo ${VER[1]} | awk '{printf ("%d",$1); exit}'`
    VER[2]=`echo ${VER[2]} | awk '{printf ("%d",$1); exit}'`
    VER[3]=`echo ${VER[3]} | awk '{printf ("%d",$1); exit}'`
    VER[4]=`echo ${VER[4]} | awk '{printf ("%d",$1); exit}'`
    VER[5]=`echo ${VER[5]} | awk '{printf ("%d",$1); exit}'`
    echoV 3 NVER=$NVER VER[]=${VER[*]}
}

compare_version () {
    # Function to compare version number from VER[] and RVER[] into res

    # Arguments are the required version
    declare -a RVER=($*)
    local n
    local res

    echoV 4 "Comparing required $*"
    echoV 4 "With VER[]=${VER[*]}"
    if [ $NVER -eq 0 ]; then
	res="OLD"
	echoV 4 $res
	return 0
    fi
    n=0
    while [ $n -lt $# ]; do
	echoV 4 n=$n x${VER[$n]}x v${RVER[$n]}v
	if [ ${VER[$n]} -lt ${RVER[$n]} ]; then
	    res="OLD"
	    echoV 4 $res
	    return 0
	elif [ ${VER[$n]} -gt ${RVER[$n]} ]; then
	    res="OK"
	    echoV 4 $res
	    return 1
	fi
	let n=$n+1
    done
    res="OK"
    echoV 4 $res
    return 1
}

ver_autoconf () {
    # Return version of autoconf

    local v

    v=`autoconf --version 2>&1 | head -n 1 | awk '{print $NF; exit}'`
    split_version $v
}
ver_autogen () {
    # Return version of autogen

    local v

    v=`autogen --version 2>&1 | head -n 1 | awk '{print $NF; exit}'`
    split_version $v
}
ver_automake () {
    # Return version of autogen

    local v

    v=`automake --version 2>&1 | head -n 1 | awk '{print $NF; exit}'`
    split_version $v
}
ver_binutils () {
    # Return version of binutils

    local v

    v=`as --version 2>&1 | head -n 1 | awk '{print $NF; exit}'`
    split_version $v
}
ver_bison () {
    # Return version of bison

    local v

    v=`bison --version 2>&1 | head -n 1 | awk '{print $NF; exit}'`
    split_version $v
}
ver_dejagnu () {
    # Return version of dejagnu

    local v

    v=`runtest --version 2>/dev/null|grep Framework|head -n 1|awk '{print $NF; exit}'`
    split_version $v
}
ver_expect () {
    # Return version of tar

    local v

    v=`expect -v 2>&1 | head -n 1 | awk '{print $NF; exit}'`
    split_version $v
}
ver_flex () {
    # Return version of flex

    local v

    v=`flex --version 2>&1 | head -n 1 | awk '{print $NF; exit}'`
    split_version $v
}
ver_gettext () {
    # Return version of gettext

    local v

    v=`gettext --version 2>&1 | head -n 1 | awk '{print $NF; exit}'`
    split_version $v
}
ver_gmp () {
    # Return version of gmp

    local v1 v2 v3
    local header

    if [ "GMPDIR" != "" ]; then
	header=$GMPDIR/include/gmp.h
    elif [ "GMPDIR64" != "" ]; then
	header=$GMPDIR64/include/gmp.h
    else
	header=/usr/include/gmp.h
    fi
    echoV 4 "ver_zlib: header: $header"
    v1=`grep MP_VERSION $header 2>&1 | head -n 1 | awk '{print $NF}'`
    v2=`grep MP_VERSION_MINOR $header 2>&1 | head -n 1 | awk '{print $NF}'`
    v3=`grep MP_VERSION_PATCHLEVEL $header 2>&1 | head -n 1 | awk '{print $NF}'`
    split_version $v1.$v2.$v3
}
ver_libtool () {
    # Return version of libtool

    local v

    v=`libtool --version 2>&1 | head -n 1 | awk '{print $4; exit}'`
    split_version $v
}
ver_m4 () {
    # Return version of m4

    local v

    v=`m4 --version 2>&1 | head -n 1 | awk '{print $NF; exit}'`
    split_version $v
}
ver_make () {
    # Return version of make

    local v

    v=`make --version 2>&1 | head -n 1 | awk '{print $NF; exit}'`
    split_version $v
}
ver_mpfr () {
    # Return version of mpfr

    local v
    local header

    if [ "MPFRDIR" != "" ]; then
	header=$MPFRDIR/include/mpfr.h
    elif [ "MPFRDIR64" != "" ]; then
	header=$MPFRDIR64/include/mpfr.h
    else
	header=/usr/include/mpfr.h
    fi
    echoV 4 "ver_zlib: header: $header"
    v=`grep MPFR_VERSION_STRING $header 2>&1 | head -n 1 | awk '{print substr($NF,2,length($NF)-2); exit}'`
    split_version $v
}
ver_pax () {
    # Return version of pax

    local v

    v=`pax --version 2>&1 | head -n 1 | awk '{print $NF; exit}'`
    split_version $v
}
ver_sed () {
    # Return version of sed

    local v

    v=`sed --version 2>&1 | head -n 1 | awk '{print $NF; exit}'`
    split_version $v
}
ver_tar () {
    # Return version of tar

    local v

    v=`tar --version 2>&1 | head -n 1 | awk '{print $NF; exit}'`
    split_version $v
}
ver_tcl () {
    # Return version of tcl

    local v

    v=`grep TCL_PATCH_LEVEL /usr/include/tcl/tcl.h 2>&1 | head -n 1 | awk '{print substr($NF,2,length($NF)-2); exit}'`
    split_version $v
}
ver_texinfo () {
    # Return version of texinfo

    local v

    v=`makeinfo --version 2>&1 | head -n 1 | awk '{print $NF; exit}'`
    split_version $v
}
ver_zlib () {
    # Return version of zlib

    local v
    local header

    if [ "$ZLIBDIR" != "" ]; then
	header=$ZLIBDIR/include/zlib.h
    else
	header=/usr/include/zlib.h
    fi
    echoV 4 "ver_zlib: header: $header"

    v=`grep ZLIB_VERSION $header 2>&1 | head -n 1 | awk '{print substr($NF,2,length($NF)-2); exit}'`
    split_version $v
}

VERSION_REQUIREMENTS=( \
    "ver_zlib" "1 2 3" \
    "ver_autoconf" "2 60" \
    "ver_autogen" "5 9 4" \
    "ver_binutils" "2 18 0" \
    "ver_bison" "2 0" \
    "ver_flex" "2 5 31" \
    "ver_gettext" "0 16 1" \
    "ver_libtool" "1 5 24" \
    "ver_m4" "1 4" \
    "ver_make" "3 81" \
    "ver_sed" "4 1 4" \
    "ver_tar" "1 19" \
    "ver_expect" "5 43 0" \
    "ver_dejagnu" "1 4 4" \
    "ver_texinfo" "4 8" \
    "ver_gmp" "4 1 4" \
    "ver_mpfr" "2 3 0" \
    "ver_tcl" "8 3 5" \
    "ver_automake" "1 10"
)

check_versions () {
    # Function to check a list of requirements

    # Arguments is a list of indexes in the REQUIREMENTS array

    local res=1

    echoV 1 "Checking version requirements"
    for r in $*; do
	func=${VERSION_REQUIREMENTS[$r]}
	ver=${VERSION_REQUIREMENTS[$r+1]}
	echoV 2 "$func"
	eval $func
	echoV 3 "   got ${func:4}:  ${VER[*]}"
	if compare_version $ver; then
	    res=0
	    pkg=${func:4}
	    echoV 1 "   IDX:$r $pkg requires $ver    got ${VER[*]}"
	fi
    done
    if [ $res -eq 0 ]; then
	echoV 1 "   Not all requirements met"
    fi
    return $res
}

insist_pkg () {
    # Function to try to find pkg in any possible compression type

    # Arguments are:
    # Package name
    local pkg=$1

    local extensions="tar.xz txz tar.gz tgz tar.bz2"

    check_numargs insist_pkg 1 $# $@

    for e in $extensions; do
	if [ -f $REPODIR/pkg/$pkg.$e ]; then PKG="$REPODIR/pkg/$pkg.$e"; return 0; fi
    done
    return 1
}

insist_wget () {
    # Function to try to wget something in any possible compression type

    # Arguments are:
    # Package name
    local pkg=$1
    # url address
    local url=$2

    local extensions="tar.xz txz tar.gz tgz tar.bz2"

    check_numargs insist_wget 2 $# $@

    for e in $extensions; do
	wget -q $url/$pkg.$e
	if [ $? = 0 ]; then TAR="$pkg.$e"; return 0; fi
	rm -f $pkg.$e
    done
    return 1
}

prepare_sources () {
    # Function to get any sources

    # Arguments are:
    # Package name, if sucessfull a directory with same name is created
    local pkg=$1
    # url address
    local url=$2

    local flag=""

    check_numargs prepare_sources 2 $# $@

    TAR=""
    PKG=""
    while true; do
	if [ -d $pkg ]; then
	    echoV 2 "Source tree: $pkg"
	    return 0
	else
	    insist_pkg $pkg
	    if [ "$PKG" = "" ]; then
		if [ "$flag" = "WGET" ]; then
		    echoV 0 "[prepare_sources] Attempt to wget failed: $url"
		    build_exit 1
		fi
		echoV 1 -n "   Importing: $url   "
		insist_wget $pkg $url
		if [ "$TAR" = "" ]; then echoV 1 "...Error"; STP=1; return
		else echoV 1 "...Ok"; fi
		mkdir -p $REPODIR/pkg
		cp -f $pkg.* $REPODIR/pkg
		rm -f $pkg.*
		flag="WGET"
	    else
		if [ "$flag" = "TAR" ]; then
		    echoV 0 "[prepare_sources] Failed to expand package: $pkg"
		    build_exit 1
		fi
		untar_any $PKG
		flag="TAR"
	    fi
	fi
    done
}

checkout_sources () {
    # Function to get the latest from source repository

    # Arguments are:
    # Name of the package to checkout
    local PKG=$1

    local GCCsvn
    local DTrepo=$BUILD_SVN
    local GCCrepo="svn://gcc.gnu.org/svn/gcc"

    check_numargs checkout_sources 1 $# $@

    echoV 1 -n -e "Checking out $PKG          "

    case $PKG in
	DTbin)
	    rm -f src_bin
	    rm -rf binutils
	    svn --quiet co $DTrepo/binutils
	    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return
	    else echoV 1 "...Ok"; fi
	    ln -s binutils src_bin
	    cd binutils
	    INFO=`svn info`
	    echoV 1 "$INFO"
	    cd ../
	    ;;
	DTgcc*)
	    rm -f src_gcc
	    if [ "$PKG" = "DTgcc" ]; then GCCsvn=gcc-trunk;
	    elif [ "$PKG" = "DTgcc45" ]; then GCCsvn=gcc-4.5-branch;
	    elif [ "$PKG" = "DTgcc46" ]; then GCCsvn=gcc-4.6-branch;
	    fi
	    rm -rf $GCCsvn
	    svn --quiet co $DTrepo/$GCCsvn
	    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return
	    else echoV 1 "...Ok"; fi
	    ln -s $GCCsvn src_gcc
	    cd $GCCsvn
	    INFO=`svn info`
	    echoV 1 "$INFO"
	    cd ../
	    ;;
	DTeglibc)
	    rm -f src_glibc src_ports src_localedef src_linuxthreads
	    rm -rf eglibc
	    svn --quiet co $DTrepo/eglibc
	    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return
	    else echoV 1 "...Ok"; fi
	    ln -s eglibc/libc src_glibc
	    ln -s eglibc/ports src_ports
	    ln -s eglibc/localedef src_localedef
	    ln -s eglibc/linuxthreads src_linuxthreads
	    ;;
	bin)
	    rm -f src_bin
	    rm -rf src binutils-$TDY
	    cvs -Q -z 9 -d :pserver:anoncvs@sourceware.org:/cvs/src co binutils
	    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return
	    else echoV 1 "...Ok"; fi
	    mv src binutils-$TDY
	    ln -s binutils-$TDY src_bin
	    ;;
	gcc4*)
	    rm -f src_gcc
	    if [ "$PKG" = "gcc44" ]; then GCCsvn=4_4;
	    elif [ "$PKG" = "gcc45" ]; then GCCsvn=4_5;
	    elif [ "$PKG" = "gcc46" ]; then GCCsvn=4_6;
	    elif [ "$PKG" = "gcc47" ]; then GCCsvn=4_7;
	    elif [ "$PKG" = "gcc48" ]; then GCCsvn=4_8;
	    elif [ "$PKG" = "gcc49" ]; then GCCsvn=4_9;
	    fi
	    rm -rf gcc-${GCCsvn}-$TDY
	    if [ ! -d ../../gcc-${GCCsvn}-$TDY ]; then
		svn --quiet checkout $GCCrepo/branches/gcc-${GCCsvn}-branch ../../gcc-${GCCsvn}-$TDY
	    fi
	    cp -rp ../../gcc-${GCCsvn}-$TDY gcc-${GCCsvn}-$TDY
	    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return
	    else echoV 1 "...Ok"; fi
	    ln -s gcc-${GCCsvn}-$TDY src_gcc
	    cd gcc-${GCCsvn}-$TDY
	    INFO=`svn info`
	    echoV 1 "$INFO"
	    cd ../
	    ;;
	gcc)
	    rm -f src_gcc
	    rm -rf gcc-$TDY
	    if [ ! -d ../../gcc-$TDY ]; then
		svn --quiet checkout $GCCrepo/trunk ../../gcc-$TDY
	    fi
	    cp -rp ../../gcc-$TDY gcc-$TDY
	    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return
	    else echoV 1 "...Ok"; fi
	    ln -s gcc-$TDY src_gcc
	    cd gcc-$TDY
	    INFO=`svn info`
	    echoV 1 "$INFO"
	    cd ../
	    ;;
	eglibc)
	    rm -f src_glibc src_ports src_localedef src_linuxthreads
	    rm -rf eglibc-$TDY
	    svn --quiet co svn://svn.eglibc.org/trunk eglibc-$TDY
	    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return
	    else echoV 1 "...Ok"; fi
	    ln -s eglibc-$TDY/libc src_glibc
	    ln -s eglibc-$TDY/ports src_ports
	    ln -s eglibc-$TDY/localedef src_localedef
	    ln -s eglibc-$TDY/linuxthreads src_linuxthreads
	    ;;
	*)
	    echoV 0 "[checkout_sources] Invalid argument for checkout_sources: $PKG"
	    build_exit 1
	    ;;
    esac
}

get_sources () {
    # Function to gather all sources necessary for this job

    # Arguments are:
    # List of sources

    # This function is also affected by the folloging env vars:
    # REPODIR

    local k p 

    for k in $@; do
	echoV 1 "Getting sources for $k"
	case $k in
	    #
	    # Standard FSF sources
	    #
	    binutils-2*)
	        rm -f src_bin
	        prepare_sources "$k" "http://cw-master-comtek.am.freescale.net/Builds/Components/Codegen/Sources"
	        ln -s $k src_bin
		;;
            gcc-4*)
	        rm -f src_gcc
	        prepare_sources "$k" "http://cw-master-comtek.am.freescale.net/Builds/Components/Codegen/Sources"
	        ln -s $k src_gcc
		;;
            linux-2.6*)
	        rm -f src_linux
	        prepare_sources "$k" "http://cw-master-comtek.am.freescale.net/Builds/Components/Codegen/Sources"
	        ln -s $k src_linux
		;;
            linux-3.19*)
	        rm -f src_linux
	        prepare_sources "$k" "http://cw-master-comtek.am.freescale.net/Builds/Components/Codegen/Sources"
	        ln -s $k src_linux
		;;
            glibc-2*)
	        rm -rf src_glibc
	        prepare_sources "$k" "hhttp://cw-master-comtek.am.freescale.net/Builds/Components/Codegen/Sources"
	        ln -s $k src_glibc
		;;
            glibc-libidn-2*)
	        rm -rf src_libidn
	        prepare_sources "$k" "http://cw-master-comtek.am.freescale.net/Builds/Components/Codegen/Sources"
		ln -s $k src_libidn
		;;
            newlib-*)
	        # Standard external sources
	        rm -rf src_newlib
	        prepare_sources "$k" "http://cw-master-comtek.am.freescale.net/Builds/Components/Codegen/Sources"
	        ln -s $k src_newlib
		;;
	    zlib-*)
	        rm -rf src_zlib
	        prepare_sources "$k" "http://cw-master-comtek.am.freescale.net/Builds/Components/Codegen/Sources"
	        ln -s $k src_zlib
		;;
	    libiconv-*)
	        rm -rf src_libiconv
	        prepare_sources "$k" "http://cw-master-comtek.am.freescale.net/Builds/Components/Codegen/Sources"
	        ln -s $k src_libiconv
		;;
	    expat-*)
	        rm -rf src_expat
	        prepare_sources "$k" "http://cw-master-comtek.am.freescale.net/Builds/Components/Codegen/Sources"
	        ln -s $k src_expat
		;;
	    gettext-*)
	        rm -rf src_gettext
	        prepare_sources "$k" "http://cw-master-comtek.am.freescale.net/Builds/Components/Codegen/Sources"
	        ln -s $k src_gettext
		;;
	    libelf-*)
	        rm -rf src_libelf
	        prepare_sources "$k" "http://cw-master-comtek.am.freescale.net/Builds/Components/Codegen/Sources"
	        ln -s $k src_libelf
		;;
	    gmp-*)
	        rm -rf src_gmp
	        prepare_sources "$k" "http://cw-master-comtek.am.freescale.net/Builds/Components/Codegen/Sources"
	        ln -s $k src_gmp
		;;
	    mpfr-*)
	        rm -rf src_mpfr
	        prepare_sources "$k" "http://cw-master-comtek.am.freescale.net/Builds/Components/Codegen/Sources"
	        ln -s $k src_mpfr
		;;
	    mpc-*)
	        rm -rf src_mpc
	        prepare_sources "$k" "http://cw-master-comtek.am.freescale.net/Builds/Components/Codegen/Sources"
	        ln -s $k src_mpc
		;;
	    ppl-*)
	        rm -rf src_ppl
	        prepare_sources "$k" "http://cw-master-comtek.am.freescale.net/Builds/Components/Codegen/Sources"
	        ln -s $k src_ppl
		;;
	    cloog-*)
	        rm -rf src_cloog
	        prepare_sources "$k" "http://cw-master-comtek.am.freescale.net/Builds/Components/Codegen/Sources"
	        ln -s $k src_cloog
		;;
	    isl-*)
	        rm -rf src_isl
	        prepare_sources "$k" "http://cw-master-comtek.am.freescale.net/Builds/Components/Codegen/Sources"
	        ln -s $k src_isl
		;;
	    libtirpc-*)
	        rm -rf src_libtirpc src_rpcheaders
	        prepare_sources "$k" "http://cw-master-comtek.am.freescale.net/Builds/Components/Codegen/Sources"
	        ln -s $k src_libtirpc
	        mkdir -p src_rpcheaders
	        cd src_rpcheaders
	        tar xjf $REPODIR/pkg/${k}-headers.tar.bz2
	        cd ../
		;;
	    tzdata2*)
	        rm -rf src_tzdata
	        prepare_sources "$k" "http://cw-master-comtek.am.freescale.net/Builds/Components/Codegen/Sources"
	        ln -s $k src_tzdata
		;;

	    localedef-2*)
	        rm -rf src_localedef
	        prepare_sources "$k" "x"
	        ln -s $k src_localedef
		;;
	    #
	    # Standard eglibc sources
	    #
	    eglibc-*)
	        # Customized sources
	        rm -rf src_glibc src_ports src_localedef src_linuxthreads
	        prepare_sources "$k" "x"
	        ln -s $k/libc src_glibc
	        ln -s $k/ports src_ports
	        ln -s $k/localedef src_localedef
	        ln -s $k/linuxthreads src_linuxthreads
	        # Set the eglibc version no
	        EGLIBC_VER=`echo $k | awk -F'[-]' '{print $2}'`
		;;
	    #
	    # Trunk checkout
	    #
	    co-*)
	        checkout_sources ${k:3}
		;;
	    #
	    # Codesourcery drops 4.2 / 4.3 / 4.4
	    # 
	    CS-eglibc-*)
	        # Customized sources
	        rm -rf src_glibc src_ports src_localedef
		prepare_sources "$k" "x"
		ln -s $k/libc src_glibc
		ln -s $k/ports src_ports
		ln -s $k/localedef src_localedef
		;;
	    CS-bin*)
	        rm -f src_bin
		prepare_sources "binutils-stable" "x"
		ln -s binutils-stable src_bin
	        ;;
	    CS-gcc-4*)
	        rm -f src_gcc
		prepare_sources "${k:3:7}" "x"
		ln -s ${k:3:7} src_gcc
	        ;;
	    CS-linux*)
	        rm -f src_linux
		prepare_sources "linux-stable" "x"
		ln -s linux-stable src_linux
	        ;;
	    CS-gmp-4.3-50*)
	        rm -f src_gmp
		prepare_sources "gmp-mirror" "x"
		ln -s gmp-mirror src_gmp
	        ;;
	    CS-gmp*)
	        rm -f src_gmp
		prepare_sources "gmp-stable" "x"
		ln -s gmp-stable src_gmp
	        ;;
	    CS-mpfr-4.3-50*)
	        rm -f src_mpfr
		prepare_sources "mpfr-mirror" "x"
		ln -s mpfr-mirror src_mpfr
	        ;;
	    CS-mpfr*)
	        rm -f src_mpfr
		prepare_sources "mpfr-stable" "x"
		ln -s mpfr-stable src_mpfr
	        ;;
	    CS-glibc_localedef-4.2*)
	        rm -f src_localedef
	        prepare_sources "glibc_localedef-2.5" "x"
		ln -s glibc_localedef-2.5 src_localedef
	        ;;
	    CS-glibc_localedef-4.3*)
	        rm -f src_localedef
	        prepare_sources "glibc_localedef-2.8" "x"
		ln -s glibc_localedef-2.8 src_localedef
	        ;;
	    CS-glibc_ports-4.2*)
	        rm -f src_ports
		prepare_sources "glibc-ports-2.5" "x"
		ln -s glibc-ports-2.5 src_ports
	        ;;
	    CS-glibc_ports-4.3*)
	        rm -f src_ports
		prepare_sources "glibc-ports-2.8" "x"
		ln -s glibc-ports-2.8 src_ports
	        ;;
	    CS-glibc-4.2*)
	        rm -f src_glibc
		prepare_sources "glibc-2.5" "x"
		ln -s glibc-2.5 src_glibc
	        ;;
	    CS-glibc-4.3*)
	        rm -f src_glibc
		prepare_sources "glibc-2.8" "x"
		ln -s glibc-2.8 src_glibc
	        ;;
	    CS-newlib*)
	        rm -f src_newlib
		prepare_sources "newlib-stable" "x"
		ln -s newlib-stable src_newlib
	        ;;
        esac
    done
    
    # Apply patches, but only once
    echoV 1 "Applying patches"
    mkdir -p patches_applied
    cp -f $REPODIR/build_gnu/f-sources/${SRCFRAG}-licenses patches_applied/FREESCALE_LICENSES
    cp -f $REPODIR/build_gnu/f-sources/${SRCFRAG}-sources patches_applied/FREESCALE_SOURCES
    for p in $setPATCHES $dLSTPATCHES; do
	k=`echo $p | awk '{split ($1,a,"."); print a[1]; exit}'`
	if [ ! -f $REPODIR/build_gnu/patches/$p ]; then
	    echoV 0 "Cannot find patch file: $REPODIR/build_gnu/patches/$p"
	    STP=1
	    return
	fi
	if [ ! -f src_$k.patched-$p ]; then
	    cp -f $REPODIR/build_gnu/patches/$p patches_applied
	    touch src_$k.patched-$p
	    cd src_$k
	    echoV 1 -n "   Patching $k with $p    "
	    patch -p1 -s < $REPODIR/build_gnu/patches/$p
	    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return
	    else echoV 1 "...Ok"; fi
	    cd ../
	fi
    done

    intergrate_sources_from_git
    
    # Complete integration when applicable
    echoV 1 "Completing source integration"
	pwd
    [ -L src_libelf ] && rm -rf src_gcc/libelf && cp -r src_libelf/ src_gcc/libelf
    [ -L src_libidn ] && rm -rf src_glibc/libidn && cp -r src_libidn/ src_glibc/libidn
    [ -L src_ports ] && rm -rf src_glibc/ports && cp -r src_ports/ src_glibc/ports
    [ -L src_gcc ] && cat $LOGFILE.dev_phase > src_gcc/gcc/DEV-PHASE
}

integrate_libraries () {

    echoV 1 "Integrating libraries into gcc sources"

    [ -L src_gmp ] && rm -rf src_gcc/gmp && cp -r src_gmp/ src_gcc/gmp
    [ -L src_mpfr ] && rm -rf src_gcc/mpfr && cp -r src_mpfr/ src_gcc/mpfr
    [ -L src_mpc ] && rm -rf src_gcc/mpc && cp -r src_mpc/ src_gcc/mpc
    [ -L src_ppl ] && rm -rf src_gcc/ppl && cp -r src_ppl/ src_gcc/ppl
    [ -L src_cloog ] && rm -rf src_gcc/cloog && cp -r src_cloog/ src_gcc/cloog
    [ -L src_isl ] && rm -rf src_gcc/isl && cp -r src_isl/ src_gcc/isl
}

intergrate_sources_from_git () {

    echoV 1 "Apply sources from GIT repository"
    [ -d $REPODIR/build_gnu/binutils ] && cp -r $REPODIR/build_gnu/binutils/.* src_bin 2>/dev/null
    [ -d $REPODIR/build_gnu/gcc ] && cp -r $REPODIR/build_gnu/gcc/.* src_gcc 2>/dev/null
    [ -d $REPODIR/build_gnu/gettext ] && cp -r $REPODIR/build_gnu/gettext/.* src_gettext 2>/dev/null
    [ -d $REPODIR/build_gnu/libelf ] && cp -r $REPODIR/build_gnu/libelf/.* src_libelf 2>/dev/null
    [ -d $REPODIR/build_gnu/newlib ] && cp -r $REPODIR/build_gnu/newlib/.* src_newlib 2>/dev/null
}

prepare_objdir () {
    # Function to initialize a build directory

    # Arguments are:
    # Name of obj build directory
    local OBJDIR=$1
    # (optional) Directory to copy from
    local SRCDIR=$2

    check_numargs prepare_objdir 1 $# $@

    if [ "$SRCDIR" != "" ]; then
	rm -rf $OBJDIR ${OBJDIR}_scratch
	cp -rp $SRCDIR $OBJDIR
	mkdir -p ${OBJDIR}_scratch
	cd ${OBJDIR}_scratch
    else
	rm -rf $OBJDIR
	mkdir -p $OBJDIR
	cd $OBJDIR
    fi
}

remove_objdir () {
    # Function to remove a build directory

    # Arguments are:
    # List of obj build directory
    local OBJDIR=$*

    check_numargs prepare_objdir 1 $# $@

    if [ "$argKEEP" = "N" ]; then
	for f in $OBJDIR; do
	    rm -rf $f ${f}_scratch
	done
    fi
}

build_cbi () {
    # Function to build anything that has the config/build/install pattern

    # Arguments are:
    # Location of configure script
    local CONFIGDIR=$1
    # Arguments of configure
    local CONFIGARGS=$2
    # Arguments of the main build
    local BUILDARGS=$3
    # Arguments of the install
    local INSTALLARGS=$4

    # This function is also affected by the folloging env vars:
    # CONFIGENV
    # BUILDENV
    # INSTALLENV
    # LOGFILE
    # NJOBS

    check_numargs build_cbi 4 $# $@

    let LN=$LN
    echo $CONFIGARGS > $LOGFILE.$LN.configargs
    echo $BUILDARGS  > $LOGFILE.$LN.buildargs
    echo $INSTALLARGS  > $LOGFILE.$LN.installargs

    let LN=$LN+1
    echoV 1 -n "   $LN config       "
    eval $CONFIGENV $CONFIGDIR/configure $CONFIGARGS > $LOGFILE.$LN.config 2>&1
    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return
    else echoV 1 "...Ok"; fi

    let LN=$LN+1
    echoV 1 -n "   $LN build        "
    eval $BUILDENV make $NJOBS $BUILDARGS > $LOGFILE.$LN.build 2>&1
    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return
    else echoV 1 "...Ok"; fi

    let LN=$LN+1
    echoV 1 -n "   $LN install      "
    $INSTALLENV make -j 1 $INSTALLARGS > $LOGFILE.$LN.install 2>&1
    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return
    else echoV 1 "...Ok"; fi
}

check_log_files () {
    if [ "$argVERBFILE" = "" ]; then
	check_dg.sh "$@"
    else
	check_dg.sh "$@" >> $argVERBFILE
    fi
}

build_lib () {
    # Build library

    # Arguments are:
    # Library name
    local LIB=$1
    # Instalal dir
    local instdir=$2
    # Extra config options
    local cfgoptions=$3
    # 32 bit config options
    local OPT32=$4
    # 64 bit config options
    local OPT64=$5

    check_numargs build_lib 5 $# $@

    local opt cfg dir

    rm -rf src_gcc/$LIB
    m=`uname -m`
    touch x.c
    ${dTBUILD}gcc -c x.c
    x=`file x.o | grep 64-bit`
    rm -f x.c x.o
    if [ "$x" = "" ]; then
	echoV 1 "Building $LIB library separately (32 bits)"
	if [ "$m" = "ppc64" ]; then HOSTDESC=HPPC32; else HOSTDESC=HIA32; fi
	opt="-m32"
	eval cfg=\"$OPT32\"
	dir=""
    else
	echoV 1 "Building $LIB library separately (64 bits)"
	if [ "$m" = "ppc64" ]; then HOSTDESC=HPPC64; else HOSTDESC=HIA64; fi
	opt="-m64"
	eval cfg=\"$OPT64\"
	dir="/64"
    fi

    I="${HOSTDESC}[0]"; HTARGET=${!I};
    I="${HOSTDESC}[1]"; HABI=${!I};
    prepare_objdir obj_$LIB
    CONFIGENV="BUILD_CC=\"${dTBUILD}gcc $opt\" CC=\"${dTBUILD}gcc $opt\" CXX=\"${dTBUILD}g++ $opt\" \
               AR=\"${dTBUILD}ar\" ABI=$HABI"
    build_cbi \
	"../src_$LIB" \
	"--prefix=${instdir}$dir $cfgoptions --build=$HTARGET --target=$HTARGET --host=$HTARGET $cfg" \
	"all" \
	"install"
    cd ../
    CONFIGENV=""

    remove_objdir obj_$LIB
}

build_canadian_lib () {
    # Build library

    # Arguments are:
    # Library name
    local lib=$1
    # Extra config options
    local cfgoptions=$2

    check_numargs build_canadian_lib 2 $# $@

    local cfg

    rm -rf src_gcc/$lib

    echoV 1 "Building $lib library separately"
    prepare_objdir obj_w_$lib
    eval cfg=\"$cfgoptions\"
    CONFIGENV="BUILD_CC=\"${dTBUILD}gcc\" CC=${dWTBUILD}gcc CXX=${dWTBUILD}g++ \
               AR=${dWTBUILD}ar RANLIB=${dWTBUILD}ranlib NM=${dWTBUILD}nm WINDRES=${dWTBUILD}windres ABI=32"
    BUILDENV="$CONFIGENV"
    build_cbi \
	"../src_$lib" \
	"--prefix=$WHOSTLIBINST/usr --build=$dTRPBUILD --target=$dTRPHOST --host=$dTRPHOST $cfg" \
	"all" \
	"install"
    cd ../
    CONFIGENV=""
    BUILDENV=""
    remove_objdir obj_w_$lib
}

build_canadian_lib_target () {
    # Build library

    # Arguments are:
    # Library name
    local lib=$1
    # Extra config options
    local cfgoptions=$2

    check_numargs build_canadian_lib_target 2 $# $@

    local cfg

    rm -rf src_gcc/$lib

    echoV 1 "Building $lib library separately"
    prepare_objdir obj_w_$lib
    eval cfg=\"$cfgoptions\"
    CONFIGENV="CC_FOR_BUILD=\"${dTRPTARGET}-gcc\" CC=${dWTBUILD}gcc CXX=${dWTBUILD}g++ \
               AR=${dWTBUILD}ar RANLIB=${dWTBUILD}ranlib NM=${dWTBUILD}nm WINDRES=${dWTBUILD}windres ABI=32"
    BUILDENV="$CONFIGENV"
    build_cbi \
	"../src_$lib" \
	"--prefix=$WHOSTLIBINST/usr --build=$dTRPBUILD --target=$dTRPTARGET --host=$dTRPHOST $cfg" \
	"all" \
	"install"
    cd ../
    CONFIGENV=""
    BUILDENV=""
    remove_objdir obj_w_$lib
}

build_bin () {
    # Build a cross binutils with sysroot method

    # Arguments are:
    # Target triplet
    local TGT=$1
    # Instalal dir
    local instdir=$2
    # Extra config options
    local cfgoptions=$3
    # Extra install options
    local INSTOPTS=$4
    # Extra BUILDENV
    local buildenv=$5
    # Directory to install manuals
    local docsdir=$6

    check_numargs build_bin 4 $# $@

    echoV 1 "Building cross binutils w/ sysroot"
    mkdir -p $docsdir/html $docsdir/pdf $docsdir/info $docsdir/man
    touch src_bin/etc/standards.texi src_bin/etc/configure.texi
    prepare_objdir obj_bin
    CONFIGENV="BUILD_CC=\"${dTBUILD}gcc\" CC=\"${dTBUILD}gcc\" CXX=\"${dTBUILD}g++\" AR=\"${dTBUILD}ar\""
    build_cbi \
	"../src_bin" \
	"--prefix=$instdir --target=$TGT $cfgoptions" \
	"$buildenv all" \
	"$INSTOPTS htmldir=$docsdir/html pdfdir=$docsdir/pdf infodir=$docsdir/info mandir=$docsdir/man install"
    cd ../

    cd obj_bin

    let LN=$LN+1
    echoV 1 -n "   $LN install html "
    make $INSTOPTS htmldir=$docsdir/html pdfdir=$docsdir/pdf infodir=$docsdir/info mandir=$docsdir/man install-html \
	>> $LOGFILE.$LN.install 2>&1
    if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
    else echoV 1 "...Ok"; fi

    let LN=$LN+1
    echoV 1 -n "   $LN install pdf  "
    make $INSTOPTS htmldir=$docsdir/html pdfdir=$docsdir/pdf infodir=$docsdir/info mandir=$docsdir/man install-pdf \
	>> $LOGFILE.$LN.install 2>&1
    if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
    else echoV 1 "...Ok"; fi

    cd ../

    CONFIGENV=""
    remove_objdir obj_bin
}

build_canadian_bin () {
    # Build a cross binutils with sysroot method

    # Arguments are:
    # Target triplet
    local TGT=$1
    # Extra config options
    local cfgoptions=$2
    # tool sysroot dir to use
    local wtoolsysroot=$3

    local CONFIGARGS

    check_numargs build_canadian_bin 3 $# $@

    echoV 1 "Building canadian zlib"

    CONFIGENV="BUILD_CC=\"${dTBUILD}gcc\" CC=\"${dWTBUILD}gcc\" CXX=\"${dWTBUILD}g++\" \
               AR=\"${dWTBUILD}ar $dWZLIBCONFIG\" RANLIB=${dWTBUILD}ranlib ABI=32"
    rm -rf obj_zlib
    cp -r src_zlib obj_zlib
    cd obj_zlib
    build_cbi \
	"../obj_zlib" \
	"--prefix=$WHOSTLIBINST/usr --static" \
	"" \
	""
    mkdir -p $WHOSTLIBINST/usr/lib
    cp -f libz.a $WHOSTLIBINST/usr/lib
    cd ../
    remove_objdir obj_zlib
    if [ "$STP" = 1 ]; then return; fi

    echoV 1 "Building canadian binutils w/ sysroot"

    prepare_objdir obj_w_bin
    touch .gnu-stamp
    CONFIGENV="BUILD_CC=\"${dTBUILD}gcc -m32\" CC=\"${dWTBUILD}gcc\" CXX=\"${dWTBUILD}g++\" \
               AR=\"${dWTBUILD}ar\" ABI=32 LDFLAGS=-L$WHOSTLIBINST/usr/lib CPPFLAGS=-I$WHOSTLIBINST/usr/include"
    CONFIGARGS="--prefix=$WTOOLINSTDIR --build=$dTRPBUILD --target=$TGT --host=$dTRPHOST --with-sysroot=$wtoolsysroot $cfgoptions"
    let LN=$LN+1
    echo $CONFIGARGS > $LOGFILE.$LN.configargs

    let LN=$LN+1
    echoV 1 -n "   $LN config       "
    eval $CONFIGENV ../src_bin/configure $CONFIGARGS > $LOGFILE.$LN.config 2>&1
    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return
    else echoV 1 "...Ok"; fi
    CONFIGENV=""

    let LN=$LN+1
    echoV 1 -n "   $LN libiberty    "
    make $NJOBS all-libiberty > $LOGFILE.$LN.build-liberty 2>&1
    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return
    else echoV 1 "...Ok"; fi

    let LN=$LN+1
    echoV 1 -n "   $LN build        "
    make $NJOBS all > $LOGFILE.$LN.build 2>&1
    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return
    else echoV 1 "...Ok"; fi

    let LN=$LN+1
    echoV 1 -n "   $LN install      "
    $INSTALLENV make $NJOBS install prefix=$WBUILDINSTDIR > $LOGFILE.$LN.install 2>&1
    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return
    else echoV 1 "...Ok"; fi
    # Create real-ld links
    rm -f $WBUILDINSTDIR/bin/${dTRPTARGET}-real-ld.exe $WBUILDINSTDIR/${dTRPTARGET}/bin/real-ld.exe
    pushd $WBUILDINSTDIR/bin >/dev/null
    ln -s ${dTRPTARGET}-ld.exe ${dTRPTARGET}-real-ld.exe
    popd >/dev/null
    pushd $WBUILDINSTDIR/${dTRPTARGET}/bin>/dev/null
    ln -s  ld.exe real-ld.exe
    popd >/dev/null
    cd ../

    rm -f $WBUILDINSTDIR/lib/charset.alias
    rm -f $WBUILDINSTDIR/bin/$dTRPTARGET-embedspu.exe
    rm -f $WBUILDINSTDIR/lib/libiberty.a
    #rmdir $WBUILDINSTDIR/lib

    NEWLIB_ORIG_PATH=${WBUILDINSTDIR}/${dINSTPREFIX}/lib
    NEWLIB_NEW_PATH=${WBUILDINSTDIR}/${dINSTPREFIX}/newlib
		
    #Move LD scripts from lib/ldscripts to newlib/lib/ldscripts
    if [ -d ${NEWLIB_ORIG_PATH} ]; then
	echoV 1 "Move LD scripts to ${NEWLIB_NEW_PATH}"
	cp -r ${NEWLIB_ORIG_PATH} ${NEWLIB_NEW_PATH}
	rm -rf ${NEWLIB_ORIG_PATH}
    fi

    for d in $dTRPTARGET/lib $dTRPTARGET/lib64 $dTRPTARGET/include/c++ lib/gcc/$dTRPTARGET; do
	if [ -d $BUILDINSTDIR/$d -a "$BUILDINSTDIR" != "$WBUILDINSTDIR" ]; then
	    mkdir -p $WBUILDINSTDIR/$d
	    cp -rf $BUILDINSTDIR/$d/* $WBUILDINSTDIR/$d
	fi
    done

    remove_objdir obj_w_bin
}

test_bin () {
    # Function to run dejagnu on binutils

    if [ ! -d obj_bin ]; then
	echoV 0 "No object directory to test"
	return
    fi

    echoV 1 "Running binutils tests"
    cd obj_bin
    make $NJOBS -k check > $LOGFILE.$LN.dejagnu 2>&1
    let LN=$LN+1
    [ -f ./binutils/binutils.log ] && cp -f ./binutils/binutils.log $LOGFILE.$LN.binutils
    [ -f ./ld/ld.log ] && cp -f ./ld/ld.log $LOGFILE.$LN.ld
    [ -f ./gas/testsuite/gas.log ] && cp -f ./gas/testsuite/gas.log $LOGFILE.$LN.gas
    check_log_files $LOGFILE.$LN.*
    cd ../
}

build_gdb () {
    # Build a cross gdb with sysroot method

    # Arguments are:
    # Target triplet
    local TGT=$1
    # Instalal dir
    local instdir=$2
    # Extra config options
    local cfgoptions=$3
    # Extra install options
    local INSTOPTS=$4
    # Extra BUILDENV
    local buildenv=$5
    # Directory to install manuals
    local docsdir=$6

    check_numargs build_gdb 4 $# $@

    echoV 1 "Building cross gdb w/ sysroot"
    mkdir -p $docsdir/html $docsdir/pdf $docsdir/info $docsdir/man
    touch src_bin/etc/standards.texi src_bin/etc/configure.texi
    prepare_objdir obj_gdb
    CONFIGENV="BUILD_CC=\"${dTBUILD}gcc\" CC=\"${dTBUILD}gcc\" CXX=\"${dTBUILD}g++\" AR=\"${dTBUILD}ar\""
    build_cbi \
	"../src_gdb" \
	"--prefix=$instdir --target=$TGT  $cfgoptions" \
	"$buildenv all" \
	"$INSTOPTS htmldir=$docsdir/html pdfdir=$docsdir/pdf infodir=$docsdir/info mandir=$docsdir/man install"
    cd ../

    cd obj_gdb

    let LN=$LN+1
    echoV 1 -n "   $LN install html "
    make $INSTOPTS htmldir=$docsdir/html pdfdir=$docsdir/pdf infodir=$docsdir/info mandir=$docsdir/man install-html \
	>> $LOGFILE.$LN.install 2>&1
    if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
    else echoV 1 "...Ok"; fi

    let LN=$LN+1
    echoV 1 -n "   $LN install pdf  "
    make $INSTOPTS htmldir=$docsdir/html pdfdir=$docsdir/pdf infodir=$docsdir/info mandir=$docsdir/man install-pdf \
	>> $LOGFILE.$LN.install 2>&1
    if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
    else echoV 1 "...Ok"; fi

    cd ../

    CONFIGENV=""
    remove_objdir obj_gdb
}

build_canadian_gdb () {
    # Build a cross gdb with sysroot method

    # Arguments are:
    # Target triplet
    local TGT=$1
    # Extra config options
    local cfgoptions=$2
    # tool sysroot dir to use
    local wtoolsysroot=$3

    local CONFIGARGS

    check_numargs build_canadian_gdb 3 $# $@

    echoV 1 "Building canadian gdb w/ sysroot"

    prepare_objdir obj_w_gdb
    touch .gnu-stamp
    CONFIGENV="BUILD_CC=\"${dTBUILD}gcc -m32\" CC=\"${dWTBUILD}gcc\" CXX=\"${dWTBUILD}g++\" \
               AR=\"${dWTBUILD}ar\" ABI=32 LDFLAGS=-L$WHOSTLIBINST/usr/lib CPPFLAGS=-I$WHOSTLIBINST/usr/include"
    CONFIGARGS="--prefix=$WTOOLINSTDIR --build=$dTRPBUILD --target=$TGT --host=$dTRPHOST --with-sysroot=$wtoolsysroot $cfgoptions"
    let LN=$LN+1
    echo $CONFIGARGS > $LOGFILE.$LN.configargs

    let LN=$LN+1
    echoV 1 -n "   $LN config       "
    eval $CONFIGENV ../src_bin/configure $CONFIGARGS > $LOGFILE.$LN.config 2>&1
    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return
    else echoV 1 "...Ok"; fi
    CONFIGENV=""

    let LN=$LN+1
    echoV 1 -n "   $LN build        "
    make $NJOBS all > $LOGFILE.$LN.build 2>&1
    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return
    else echoV 1 "...Ok"; fi

    let LN=$LN+1
    echoV 1 -n "   $LN install      "
    $INSTALLENV make $NJOBS install prefix=$WBUILDINSTDIR > $LOGFILE.$LN.install 2>&1
    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return
    else echoV 1 "...Ok"; fi

    remove_objdir obj_w_gdb
}

CROSS_GCC_CONFIG="--with-long-double-128 --enable-poison-system-directories \
    --with-gnu-as --with-gnu-ld --disable-libstdcxx-pch \
    --disable-libssp --disable-libmudflap \
    --disable-bootstrap --disable-libquadmath \
    --disable-nls --enable-symvers=gnu --disable-__cxa_atexit"

build_cross_gcc_1 () {
    # Build a cross gcc without headers (multilib or not)

    # Arguments are:
    # Target triplet
    local TGT=$1
    # Sysroot dir
    local sys=$2
    # Instalal dir
    local instdir=$3
    # (optional) Extra config options
    local cfgoptions=$4

    check_numargs build_cross_gcc_1 3 $# $@

    rm -f $instdir/lib/libiberty.a $instdir/'bin/*gccbug' $instdir/'bin/gccbug*'
    rm -f $instdir/lib/charset.alias $instdir/bin/$TGT-embedspu

    echoV 1 "Building cross gcc w/o headers"
    local MINOPTS="$CROSS_GCC_CONFIG --disable-libgomp \
        --without-headers --with-newlib --disable-shared --disable-threads \
	--enable-languages=c --disable-decimal-float"
    prepare_objdir obj_gccmin
    export LD_LIBRARY_PATH=$LDPATH
    build_cbi \
	"../src_gcc" \
	"--prefix=$instdir --target=$TGT $MINOPTS $cfgoptions" \
	"all" \
	"install"
    cd ../
    remove_objdir obj_gccmin

    rm -f $instdir/lib/libiberty.a $instdir/'bin/*gccbug' $instdir/'bin/gccbug*'
    rm -f $instdir/lib/charset.alias $instdir/bin/$TGT-embedspu
    touch $sys/usr/include/assert.h > /dev/null 2>&1
}

build_cross_gcc_2 () {
    # Build a minimum cross gcc with sysroot (multilib or not)

    # Arguments are:
    # Target triplet
    local TGT=$1
    # (optional) Extra config options
    local cfgoptions=$2

    check_numargs build_cross_gcc_2 1 $# $@

    rm -f $BUILDINSTDIR/lib/libiberty.a $BUILDINSTDIR/'bin/*gccbug' $BUILDINSTDIR/'bin/gccbug*'
    rm -f $BUILDINSTDIR/lib/charset.alias $BUILDINSTDIR/bin/$TGT-embedspu

    echoV 1 "Building minimum cross gcc with sysroot"
    local MINOPTS="$CROSS_GCC_CONFIG --disable-libgomp \
        --prefix=$TOOLINSTDIR --with-sysroot=$TOOLSYSROOT --with-build-sysroot=$BUILDSYSROOT \
        --with-build-time-tools=$BUILDINSTDIR/$dTRPTARGET/bin \
	--enable-languages=c --disable-decimal-float --disable-libstdcxx-pch"
    prepare_objdir obj_gccsys
    export LD_LIBRARY_PATH=$LDPATH
    build_cbi \
	"../src_gcc" \
	"--target=$TGT $MINOPTS $cfgoptions" \
	"all LDFLAGS_FOR_TARGET=--sysroot=$BUILDSYSROOT CPPFLAGS_FOR_TARGET=--sysroot=$BUILDSYSROOT \
            build_tooldir=$BUILDINSTDIR/$dTRPTARGET" \
	"install prefix=$BUILDINSTDIR"
    cd ../
    remove_objdir obj_gccsys
}

build_cross_gcc_final () {
    # Build a full cross gcc with sysroot

    # Arguments are:
    # Target triplet
    local TGT=$1
    # (optional) Extra config options
    local cfgoptions=$2
    local docsdir=$BUILDSYSROOT/share/docs

    check_numargs build_cross_gcc_final 1 $# $@

    echoV 1 "Building full cross gcc with sysroot"
    local MINOPTS="$CROSS_GCC_CONFIG --enable-threads \
        --prefix=$TOOLINSTDIR --with-sysroot=$TOOLSYSROOT --with-build-sysroot=$BUILDSYSROOT \
        --with-build-time-tools=$BUILDINSTDIR/$dTRPTARGET/bin \
	--enable-languages=c,c++,fortran"
    prepare_objdir obj_gcc
    export LD_LIBRARY_PATH=$LDPATH
    # To debug gcc
    # CONFIGENV="CFLAGS=\"-O0 -g\" LFLAGS=-g"
    build_cbi \
	"../src_gcc" \
	"--target=$TGT $MINOPTS $cfgoptions" \
	"all LDFLAGS_FOR_TARGET=--sysroot=$BUILDSYSROOT CPPFLAGS_FOR_TARGET=--sysroot=$BUILDSYSROOT \
            LIBTOOLHACK=-Wc,--sysroot=$BUILDSYSROOT build_tooldir=$BUILDINSTDIR/$dTRPTARGET" \
	"prefix=$BUILDINSTDIR htmldir=$docsdir/html pdfdir=$docsdir/pdf infodir=$docsdir/info mandir=$docsdir/man install"

    let LN=$LN+1
    echoV 1 -n "   $LN install html "
    make prefix=$BUILDINSTDIR htmldir=$docsdir/html pdfdir=$docsdir/pdf infodir=$docsdir/info mandir=$docsdir/man install-html \
	>> $LOGFILE.$LN.install 2>&1
    if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
    else echoV 1 "...Ok"; fi

    let LN=$LN+1
    echoV 1 -n "   $LN install pdf  "
    make prefix=$BUILDINSTDIR htmldir=$docsdir/html pdfdir=$docsdir/pdf infodir=$docsdir/info mandir=$docsdir/man install-pdf \
	>> $LOGFILE.$LN.install 2>&1
    if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
    else echoV 1 "...Ok"; fi
    CONFIGENV=

    local LDIR

    let LN=$LN+1
    echo -n "" > $LOGFILE.$LN.sysroot_copy
    for LDIR in lib64 lib; do
	if [ -e $BUILDINSTDIR/$TGT/$LDIR/libgcc_s.so ]; then
	    echoV 1 -n "   copy libgcc_s    "
	    cp -d $BUILDINSTDIR/$TGT/$LDIR/libgcc_s.so* $BUILDSYSROOT/usr/$LDIR \
		>> $LOGFILE.$LN.sysroot_copy 2>&1
	    if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
	    else echoV 1 "...Ok"; fi
	fi
	if [ -e $BUILDINSTDIR/$TGT/$LDIR/libstdc++.so ]; then
	    echoV 1 -n "   copy libstdc++   "
	    cp -d $BUILDINSTDIR/$TGT/$LDIR/libstdc++.so* $BUILDSYSROOT/usr/$LDIR \
		>> $LOGFILE.$LN.sysroot_copy 2>&1
	    if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
	    else echoV 1 "...Ok"; fi
	fi
	if [ -e $BUILDINSTDIR/$TGT/$LDIR/libgfortran.so ]; then
	    echoV 1 -n "   copy libgfortran "
            cp -d $BUILDINSTDIR/$TGT/$LDIR/libgfortran.so* $BUILDSYSROOT/usr/$LDIR \
		>> $LOGFILE.$LN.sysroot_copy 2>&1
	    if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
	    else echoV 1 "...Ok"; fi
	fi
    done

    cd ../
    remove_objdir obj_gcc
}

build_canadian_gcc () {
    # Build a full cross gcc with sysroot

    # Arguments are:
    # Target triplet
    local TGT=$1
    # (optional) Extra config options
    local cfgoptions=$2
    # build sysroot dir to use
    local wbuildsysroot=$3
    # tool sysroot dir to use
    local wtoolsysroot=$4

    check_numargs build_canadian_gcc 4 $# $@

    echoV 1 "Building canadian gcc with sysroot"
    local MINOPTS="$CROSS_GCC_CONFIG  --enable-threads \
        --prefix=$WTOOLINSTDIR --with-sysroot=$wtoolsysroot --with-build-sysroot=$wbuildsysroot \
        --with-build-time-tools=$WBUILDINSTDIR/$dTRPTARGET/bin \
	--enable-languages=c,c++,fortran"
    [ "$wbuildsysroot" = "$WEBUILDSYSROOT" -a ! -e $wbuildsysroot/usr/include ] \
	&& mkdir -p $wbuildsysroot/usr && cp -r ./src_bin/include $wbuildsysroot/usr/include
    prepare_objdir obj_w_gcc
    export LD_LIBRARY_PATH=$LDPATH
    CONFIGENV="BUILD_CC=\"${dTBUILD}gcc\" CC=\"${dWTBUILD}gcc\" CXX=\"${dWTBUILD}g++\" \
               AR=\"${dWTBUILD}ar\" ABI=32 AR_FOR_TARGET=$dTRPTARGET-ar NM_FOR_TARGET=$dTRPTARGET-nm \
               OBJDUMP_FOR_TARGET=$dTRPTARGET-objdump STRIP_FOR_TARGET=$dTRPTARGET-strip \
               CC_FOR_TARGET=$dTRPTARGET-gcc GCC_FOR_TARGET=$dTRPTARGET-gcc CXX_FOR_TARGET=$dTRPTARGET-g++"
    # To debug gcc
    # CONFIGENV="CFLAGS=\"-O0 -g\" LFLAGS=-g $CONFIGENV"
    build_cbi \
	"../src_gcc" \
	"--build=$dTRPBUILD --target=$TGT --host=$dTRPHOST $MINOPTS $cfgoptions" \
	"all-gcc LDFLAGS_FOR_TARGET=--sysroot=$wbuildsysroot CPPFLAGS_FOR_TARGET=--sysroot=$wbuildsysroot build_tooldir=$WBUILDINSTDIR/$dTRPTARGET" \
	"install-gcc prefix=$WBUILDINSTDIR"
    cd ../
    CONFIGENV=""
    if [ "$STP" = "1" ]; then return; fi

    for d in $dTRPTARGET/lib $dTRPTARGET/lib64 $dTRPTARGET/include/c++ lib/gcc/$dTRPTARGET; do
	if [ -d $BUILDINSTDIR/$d -a "$BUILDINSTDIR" != "$WBUILDINSTDIR" ]; then
	    mkdir -p $WBUILDINSTDIR/$d
	    cp -rf $BUILDINSTDIR/$d/* $WBUILDINSTDIR/$d
	fi
    done

    remove_objdir obj_w_gcc
}

build_native_gcc () {
    # Build a native gcc

    # Arguments are:
    # Target triplet
    local TGT=$1
    # target of makefile
    local maketgt=$2
    # (optional) Extra config options
    local cfgoptions=$3
    local docsdir=$BUILDINSTDIR/$dTRPTARGET/share/docs

    check_numargs build_native_gcc 2 $# $@

    echoV 1 "Building native gcc"
    local MINOPTS="--build=$TGT --enable-checking \
	--disable-decimal-float --enable-interfaces=c,c++"
    prepare_objdir obj_gcc
    export LD_LIBRARY_PATH=$LDPATH
    #ONFIGENV="BUILD_CC=\"${dTBUILD}gcc\" CC=\"${dTBUILD}gcc\" AR=\"${dTBUILD}ar\""
    build_cbi \
	"../src_gcc" \
	"--prefix=$BUILDINSTDIR --target=$TGT $MINOPTS $cfgoptions" \
	"$maketgt $dGCCMAKE" \
	"htmldir=$docsdir/html pdfdir=$docsdir/pdf infodir=$docsdir/info mandir=$docsdir/man install"

    let LN=$LN+1
    echoV 1 -n "   $LN install html "
    make htmldir=$docsdir/html pdfdir=$docsdir/pdf infodir=$docsdir/info mandir=$docsdir/man install-html \
	>> $LOGFILE.$LN.install 2>&1
    if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
    else echoV 1 "...Ok"; fi

    let LN=$LN+1
    echoV 1 -n "   $LN install pdf  "
    make htmldir=$docsdir/html pdfdir=$docsdir/pdf infodir=$docsdir/info mandir=$docsdir/man install-pdf \
	>> $LOGFILE.$LN.install 2>&1
    if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
    else echoV 1 "...Ok"; fi
    CONFIGENV=""
    cd ../

    echoV 1 -n "Copying gcc libs to sysroot   "
    cp -a $BUILDINSTDIR/lib $BUILDINSTDIR/$TGT
    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return
    else echoV 1 "...Ok"; fi
    if [ -e $BUILDINSTDIR/lib64 ]; then
	echoV 1 -n "Copying gcc libs to sysroot   "
	cp -a $BUILDINSTDIR/lib64 $BUILDINSTDIR/$TGT
	if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return
	else echoV 1 "...Ok"; fi
    fi

    remove_objdir obj_gcc
}

EABI_GCC_CONFIG="--disable-shared --disable-threads --disable-decimal-float \
    --with-gnu-as --with-gnu-ld --disable-libstdcxx-pch \
    --disable-libssp --disable-libmudflap \
    --disable-nls"

build_cross_gcc_eabi_alt () {
    # Build a cross gcc without headers (multilib or not)

    # Arguments are:
    # Target triplet
    local TGT=$1
    # (optional) Extra config options
    local cfgoptions=$2

    check_numargs build_cross_gcc_eabi_alt 1 $# $@

    echoV 1 "Building cross gcc w/o headers"
    #mkdir -p $EBUILDSYSROOT
    #cp -rf src_newlib/newlib/libc/include $EBUILDSYSROOT
    #ln -s $EBUILDSYSROOT/include $BUILDINSTDIR/include
    # To debug gcc
    #CONFIGENV="CFLAGS=\"-O0 -g\" CXXFLAGS=\"-O0 -g\" LFLAGS=-g"
    cp -rf src_newlib/newlib/libc/include $BUILDINSTDIR
    local MINOPTS="$EABI_GCC_CONFIG --with-newlib \
        --prefix=$TOOLINSTDIR --with-sysroot=$ETOOLSYSROOT --with-build-sysroot=$EBUILDSYSROOT \
        --with-built-time-tools=$BUILDINSTDIR/bin \
	--without-headers --disable-libgomp --enable-languages=c"
    prepare_objdir obj_gccmin
    build_cbi \
	"../src_gcc" \
	"--target=$TGT $MINOPTS $cfgoptions" \
	"all LDFLAGS_FOR_TARGET=--sysroot=$EBUILDSYSROOT CPPFLAGS_FOR_TARGET=--sysroot=$EBUILDSYSROOT build_tooldir=$BUILDINSTDIR" \
	"install prefix=$BUILDINSTDIR"
    cd ../
    remove_objdir obj_gccmin
}

build_libaeabi () {
    # Compile the functions that support hosted execution of aeabi code

    # Arguments are
    # Build installation dir (ex: BUILDINSTDIR)
    local buildinst=$1

    # Global variables used
    # dTRPTARGET

    check_numargs build_libaeabi 1 $# $@

    # Local variables
    local x objs f tgt GCCDIR LIBAEABI_AS LIBAEABI_C srcdir
    # Executables
    local GCC=$buildinst/bin/${dTRPTARGET}-gcc
    local AR=$buildinst/bin/${dTRPTARGET}-ar

    # Calculate directories
    x=`$GCC -print-libgcc-file-name`
    GCCDIR=`dirname $x`

    LIBAEABI_AS="sim-getrusage simulator mcount"
    LIBAEABI_C="sim-abort sim-errno sim-inbyte sim-print sim-sbrk fstat getpid isatty kill putnum stat unlink"
    srcdir="`pwd`/src_gcc/gcc/config/rs6000/libaeabi"

    objs=""
    for f in $LIBAEABI_AS $LIBAEABI_C; do
	objs="$objs $f.o"
    done
    for tgt in 32 64; do
	echoV 1 "Building libaeabi for $tgt"
	rm -rf obj_libaeabi_$tgt
	mkdir -p obj_libaeabi_$tgt
	cd obj_libaeabi_$tgt
	$GCC -c -m$tgt $srcdir/crtaeabi0.S
	$GCC -c -m$tgt $srcdir/crtaeabi9.S
	for f in $LIBAEABI_AS; do
            $GCC -c -m$tgt $srcdir/$f.S
	done
	for f in $LIBAEABI_C; do
            $GCC -O2 -c -m$tgt $srcdir/$f.c
	done
	$AR r libaeabi.a $objs >/dev/null 2>&1
	cd ../
    done

    echoV 1 "Installing libaeabi on tools dir"
    cp -f obj_libaeabi_32/crtaeabi0.o obj_libaeabi_32/crtaeabi9.o obj_libaeabi_32/libaeabi.a $GCCDIR
    cp -f obj_libaeabi_64/crtaeabi0.o obj_libaeabi_64/crtaeabi9.o obj_libaeabi_64/libaeabi.a $GCCDIR/64

    echoV 1 "Installing libaeabi for dejagnu runs"
    cp -f obj_libaeabi_32/crtaeabi0.o obj_libaeabi_32/crtaeabi9.o obj_libaeabi_32/libaeabi.a obj_gcc/gcc
    cp -f obj_libaeabi_64/crtaeabi0.o obj_libaeabi_64/crtaeabi9.o obj_libaeabi_64/libaeabi.a obj_gcc/gcc/64
}

build_cross_gcc_eabi_final () {
    # Build a full cross gcc with sysroot

    # Arguments are:
    # Target triplet
    local TGT=$1
    # (optional) Extra config options
    local cfgoptions=$2
    local docsdir=$EBUILDSYSROOT/share/docs

    check_numargs build_cross_gcc_eabi_final 1 $# $@

    # To debug gcc
    # CONFIGENV="CFLAGS=\"-O0 -g\" CXXFLAGS=\"-O0 -g\" LFLAGS=-g"
    echoV 1 "Building full cross gcc with sysroot"
    local MINOPTS="$EABI_GCC_CONFIG --with-newlib \
        --prefix=$TOOLINSTDIR --with-sysroot=$ETOOLSYSROOT --with-build-sysroot=$EBUILDSYSROOT \
        --with-built-time-tools=$BUILDINSTDIR/bin \
	--with-headers=yes --enable-languages=c,c++"
#	--with-headers=yes --enable-languages=c,c++,fortran"
    mkdir -p $EBUILDSYSROOT/usr
    cp -r ./src_bin/include $EBUILDSYSROOT/usr/include
    prepare_objdir obj_gcc
    build_cbi \
	"../src_gcc" \
	"--target=$TGT $MINOPTS $cfgoptions" \
	"all LDFLAGS_FOR_TARGET=--sysroot=$EBUILDSYSROOT CPPFLAGS_FOR_TARGET=--sysroot=$EBUILDSYSROOT build_tooldir=$BUILDINSTDIR" \
	"prefix=$BUILDINSTDIR htmldir=$docsdir/html pdfdir=$docsdir/pdf infodir=$docsdir/info mandir=$docsdir/man install"

    let LN=$LN+1
    echoV 1 -n "   $LN install html "
    make prefix=$BUILDINSTDIR htmldir=$docsdir/html pdfdir=$docsdir/pdf infodir=$docsdir/info mandir=$docsdir/man install-html \
	>> $LOGFILE.$LN.install 2>&1
    if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
    else echoV 1 "...Ok"; fi

    let LN=$LN+1
    echoV 1 -n "   $LN install pdf  "
    make prefix=$BUILDINSTDIR htmldir=$docsdir/html pdfdir=$docsdir/pdf infodir=$docsdir/info mandir=$docsdir/man install-pdf \
	>> $LOGFILE.$LN.install 2>&1
    if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
    else echoV 1 "...Ok"; fi
    cd ../

    remove_objdir obj_gcc
}

build_cross_gcc_eabi_nano () {
    # Build GCC to get nano version of standard libraries

    # Arguments are:
    # Target triplet
    local TGT=$1
    # (optional) Extra config options
    local cfgoptions=$2
    local docsdir=$EBUILDSYSROOT/share/docs

    check_numargs build_cross_gcc_eabi_final 1 $# $@
    
    CONFIGENV="CXXFLAGS_FOR_TARGET=\"-g -Os -ffunction-sections -fdata-sections -fno-exceptions\""
    
    echoV 1 "Building GCC for nano version of standard libraries"
    local MINOPTS="$EABI_GCC_CONFIG --with-newlib \
        --prefix=$TOOLINSTDIR --with-sysroot=$ETOOLSYSROOT --with-build-sysroot=$EBUILDSYSROOT \
        --with-built-time-tools=$BUILDINSTDIR/bin \
        --with-headers=yes --enable-languages=c,c++ \
        --disable-decimal-float \
        --disable-libffi \
        --disable-libgomp \
        --disable-libmudflap \
        --disable-libquadmath \
        --disable-libssp \
        --disable-libstdcxx-pch \
        --disable-nls \
        --disable-shared \
        --disable-threads \
        --disable-tls \
        --with-gnu-as \
        --with-gnu-ld"
    
    pushd $(pwd) >/dev/null
        
    mkdir -p $EBUILDSYSROOT/usr
    cp -r ./src_bin/include $EBUILDSYSROOT/usr/include
    
    prepare_objdir obj_gcc
    build_cbi \
        "../src_gcc" \
        "--target=$TGT $MINOPTS $cfgoptions" \
        "all LDFLAGS_FOR_TARGET=--sysroot=$EBUILDSYSROOT CPPFLAGS_FOR_TARGET=--sysroot=$EBUILDSYSROOT build_tooldir=$BUILDINSTDIR" \
        "prefix=$BUILDINSTDIR htmldir=$docsdir/html pdfdir=$docsdir/pdf infodir=$docsdir/info mandir=$docsdir/man install"

    remove_objdir obj_gcc

    popd >/dev/null
    CONFIGENV=""

}

test_gcc () {
    # Function to run dejagnu on multilib gcc

    # Arguments are:
    # Target triplet
    local TGT=$1
    # Instalal dir
    local instdir=$2

    check_numargs test_gcc 2 $# $@

    local i m libdir bname sfx sysflags mlosdir mldir

    if [ ! -d obj_gcc ]; then
	echoV 0 "No object directory to test"
	return
    fi
    if [ "$DGDESC" = "" ]; then
	echoV 0 "No DGDESC is set. Use command t=<..>"
	return
    fi

    echoV 1 "Running gcc dejagnu"

    cd obj_gcc
    if [ "$dBRDTYPE" = "noboard" ]; then
	echoV 1 "Full test"
	let LN=$LN+1
	echo "$TESTFLAGS $dBRDRUNTESTFLAGS" > $LOGFILE.$LN.runtestflags 2>&1
	let LN=$LN+1
	make $NJOBS -k check \
	    RUNTESTFLAGS="$TESTFLAGS $dBRDRUNTESTFLAGS" > $LOGFILE.$LN.dejagnu 2>&1
	let LN=$LN+1
	test_savelogs $LN gcc/testsuite/*/*.log $TGT/*/testsuite/*.log
	check_log_files $LOGFILE.$LN.*	    
    else
	m=0
	while [ $m -lt $dMLSIZE ]; do
	    echoV 1 "   multilib [$m]"
	    sfx=$RANDOM
	    let LN=$LN+1
	    test_copylibs $LN $instdir/$TGT $m $sfx
	    
	    bname=${dBRDNAME}
	    libdir=${dBRDLIBDIR}
	    mlosdir=${aMLOSDIRS[$m]}
	    mldir=${aMLDIRS[$m]}
	    let LN=$LN+1
	    if [ "$libdir" != "" ]; then
		echoV 2 "Gcc test only"
		libdir=${libdir}_$sfx
		test_fixboard $bname $sfx "$mlosdir" $libdir $libdir/libc $instdir/$TGT/libc "$mldir"
		echo "$TESTFLAGS $dBRDRUNTESTFLAGS CFLAGS_FOR_TARGET=--sysroot=$instdir/$TGT/libc --target_board=${bname}${sfx}${aMLDEJAGNU[$m]}" \
		    > $LOGFILE.$LN.runtestflags 2>&1
		let LN=$LN+1
		make $NJOBS -k check-gcc \
		    RUNTESTFLAGS="$TESTFLAGS $dBRDRUNTESTFLAGS CFLAGS_FOR_TARGET=--sysroot=$instdir/$TGT/libc --target_board=${bname}${sfx}${aMLDEJAGNU[$m]}" \
		    > $LOGFILE.$LN.dejagnu 2>&1
	    else
		echoV 2 "Full test"
		test_fixboard $bname $sfx "$mlosdir" $instdir/$TGT $instdir/$TGT $instdir/$TGT "$mldir"
		sysflags="CFLAGS_FOR_TARGET=--sysroot=$instdir/$TGT"
		echo "$TESTFLAGS $dBRDRUNTESTFLAGS $sysflags --target_board=${bname}${sfx}${aMLDEJAGNU[$m]}" \
		    > $LOGFILE.$LN.runtestflags 2>&1
		let LN=$LN+1
		make $NJOBS -k check \
		    RUNTESTFLAGS="$TESTFLAGS $dBRDRUNTESTFLAGS $sysflags --target_board=${bname}${sfx}${aMLDEJAGNU[$m]}" \
		    > $LOGFILE.$LN.dejagnu 2>&1
	    fi
	    rm -f $REPODIR/build_gnu/boards/${bname}$sfx.exp
	    let LN=$LN+1
	    test_remlibs $LN $m $sfx
	    
	    let LN=$LN+1
	    test_savelogs $LN gcc/testsuite/*/*.log $TGT/*/testsuite/*.log
	    check_log_files $LOGFILE.$LN.*
	    
	    let m=$m+1
	done
        # Reset individual tests setup
	TESTFLAGS=""
	let LN=$LN+1
	test_FSFreport $LN
    fi
    cd ../
}

test_gcc_eabi () {
    # Function to run dejagnu on multilib gcc

    # Arguments are:
    # Target triplet
    local TGT=$1
    # Instalal dir
    local instdir=$2

    check_numargs test_gcc 2 $# $@

    local i m libdir bname sfx sysflags mlosdir mldir

    if [ ! -d obj_gcc ]; then
	echoV 0 "No object directory to test"
	return
    fi
    if [ "$DGDESC" = "" ]; then
	echoV 0 "No DGDESC is set. Use command t=<..>"
	return
    fi

    echoV 1 "Running gcc dejagnu"

    cd obj_gcc
	    
    bname=${dBRDNAME}
    libdir=${dBRDLIBDIR}
    sfx=$RANDOM
    let LN=$LN+1
    libdir=${libdir}_$sfx
    test_fixboard_eabi $bname $sfx $libdir $libdir/libc $instdir/$TGT/libc
    echo "$TESTFLAGS $dBRDRUNTESTFLAGS CFLAGS_FOR_TARGET=\\\\\\\"-I $instdir/$TGT/include --sysroot=$instdir/$TGT\\\\\\\" --target_board=${bname}${sfx}" \
	> $LOGFILE.$LN.runtestflags 2>&1
    let LN=$LN+1
    make $NJOBS -k check-gcc \
	RUNTESTFLAGS="$TESTFLAGS -v -v $dBRDRUNTESTFLAGS CFLAGS_FOR_TARGET=\\\\\\\"-I $instdir/$TGT/include --sysroot=$instdir/$TGT\\\\\\\" --target_board=${bname}${sfx}" \
	> $LOGFILE.$LN.dejagnu 2>&1
    rm -f $REPODIR/build_gnu/boards/${bname}$sfx.exp
    let LN=$LN+1
    test_remlibs $LN 0 $sfx
    let LN=$LN+1
    test_savelogs $LN gcc/testsuite/*/*.log $TGT/*/testsuite/*.log
    check_log_files $LOGFILE.$LN.*
	    
    # Reset individual tests setup
    TESTFLAGS=""
    cd ../
}

test_gcc_bm () {
    # Function to run dejagnu on multilib gcc

    # Arguments are:
    # Target triplet
    local TGT=$1
    # Instalal dir
    local instdir=$2

    check_numargs test_gcc 2 $# $@

    local i m

    if [ ! -d obj_gcc ]; then
	echoV 0 "No object directory to test"
	return
    fi

    echoV 1 "Running gcc dejagnu"

    cd obj_gcc
    echoV 2 "Full test"
    let LN=$LN+1
    make $NJOBS -k check-gcc \
	RUNTESTFLAGS="$TESTFLAGS $dBRDRUNTESTFLAGS" > $LOGFILE.$LN.dejagnu 2>&1
    test_savelogs $LN gcc/testsuite/*/*.log $TGT/*/testsuite/*.log
    check_log_files $LOGFILE.$LN.*	    
    cd ../
}

build_linuxhdrs () {
    # Function to build linux header files

    # Arguments are:
    # Architecture
    local ARCH=$1
    # Target triplet
    local TGT=$2
    # Installation dir
    local instdir=$3

    # This function is also affected by the folloging env vars:
    # BUILDENV
    # LOGFILE
    # NJOBS

    check_numargs build_linuxhdrs 3 $# $@

    echoV 1 "Building linux headers for $ARCH"
    rm -rf obj_linux
    cp -r src_linux/ obj_linux
    cd obj_linux
    echoV 1 -n "   $LN install      "
    $BUILDENV make $NJOBS headers_install \
	ARCH=$ARCH CROSS_COMPILE=$TGT- \
	INSTALL_HDR_PATH=$instdir > $LOGFILE.$LN.linuxhdrs 2>&1
    if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
    else echoV 1 "...Ok"; fi
    cd ../
    remove_objdir obj_linux
}

CROSS_GLIBC_CONFIG="--disable-profile --without-gd --without-cvs \
        --prefix=/usr libc_cv_c_cleanup=yes"

build_glibchdrs () {
    # Function to build glibc header files (multilib or not)

    # Arguments are:
    # Target triplet
    local TGT=$1
    # Sysroot dir
    local sys=$2
    # (optional) Extra config options
    local cfgoptions=$3

    local idx
    local t

    # This function is also affected by the folloging env vars:
    # LOGFILE
    # NJOBS

    check_numargs build_glibchdrs 3 $# $@

    local MINOPTS="$CROSS_GLIBC_CONFIG \
	--build=$(src_glibc/scripts/config.guess) \
	--with-headers=$sys/usr/include"

    idx=0
    while [ $idx -lt $dMLSIZE ]; do
	echoV 1 "Building glibc headers [$idx]"
	prepare_objdir obj_glibchdrs_$idx src_glibc/

	t=${aMLTARGET[$idx]}
	if [ "$t" = "" ]; then
	    t=$TGT
	fi
	let LN=$LN+1
	echo "$MINOPTS --host=$t ${aMLCONFIG[$idx]} $cfgoptions" \
	    > $LOGFILE.$LN.configargs

	let LN=$LN+1
	if [ "$t" != "$TGT" -a ! -e $BUILDINSTDIR/bin/$t-readelf ]; then
	    # Quick hack to avoid error on CDE builds (eglibc-2.15)
	    ln -s $TGT-readelf $BUILDINSTDIR/bin/$t-readelf
	    # Quick hack to avoid error on CDE builds (eglibc-2.19)
	    ln -s $TGT-nm $BUILDINSTDIR/bin/$t-nm
	fi
	echoV 1 -n "   $LN config       "
	BUILD_CC=gcc CC="$TGT-gcc ${aMLCFLAGS[$idx]}" \
	    CXX="$TGT-g++ ${aMLCFLAGS[$idx]}" \
	    AR=$TGT-ar RANLIB=$TGT-ranlib \
	    ../obj_glibchdrs_$idx/configure $MINOPTS --host=$t \
	    ${aMLCONFIG[$idx]} $cfgoptions \
	    > $LOGFILE.$LN.glibchdrs-config 2>&1
	if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
	else echoV 1 "...Ok"; fi

	let LN=$LN+1
	echoV 1 -n "   $LN install      "
	make $NJOBS install-bootstrap-headers=yes install-headers \
	    install_root=$sys/${aMLDIRS[$idx]} \
	    > $LOGFILE.$LN.glibchdrs-install 2>&1
	if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
	else echoV 1 "...Ok"; fi
	
	mkdir -p $sys/${aMLDIRS[$idx]}/usr/lib/${aMLOSDIRS[$idx]}
	echoV 1 -n "   set stdio_lim.h  "
	cp bits/stdio_lim.h $sys/${aMLDIRS[$idx]}/usr/include/bits/stdio_lim.h
	if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
	else echoV 1 "...Ok"; fi
	echoV 1 -n "   set stubs.h      "
	cp /dev/null $sys/${aMLDIRS[$idx]}/usr/include/gnu/stubs.h
	if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
	else echoV 1 "...Ok"; fi

	let LN=$LN+1
	echoV 1 -n "   $LN build csu    "
	make csu/subdir_lib > $LOGFILE.$LN.glibchdrs-csu.build 2>&1
	if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
	else echoV 1 "...Ok"; fi

	let LN=$LN+1
	echoV 1 -n "   $LN copy crt1.o  "
	cp csu/crt1.o $sys/${aMLDIRS[$idx]}/usr/lib/${aMLOSDIRS[$idx]} \
	    > $LOGFILE.$LN.glibchdrs-libcso 2>&1
	if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
	else echoV 1 "...Ok"; fi
	echoV 1 -n "   $LN copy crti.o  "
	cp csu/crti.o $sys/${aMLDIRS[$idx]}/usr/lib/${aMLOSDIRS[$idx]} \
	    >> $LOGFILE.$LN.glibchdrs-libcso 2>&1
	if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
	else echoV 1 "...Ok"; fi
	echoV 1 -n "   $LN copy crtn.o  "
	cp csu/crtn.o $sys/${aMLDIRS[$idx]}/usr/lib/${aMLOSDIRS[$idx]} \
	    >> $LOGFILE.$LN.glibchdrs-libcso 2>&1
	if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
	else echoV 1 "...Ok"; fi
	echoV 1 -n "   $LN set libc.so  "
	$TGT-gcc ${aMLCFLAGS[$idx]} -nostdlib -nostartfiles -shared -x c \
	    /dev/null -o $sys/${aMLDIRS[$idx]}/usr/lib/${aMLOSDIRS[$idx]}/libc.so \
	    >> $LOGFILE.$LN.glibchdrs-libcso 2>&1
	if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
	else echoV 1 "...Ok"; fi

	cd ../
	let idx=$idx+1
    done
    remove_objdir obj_glibchdrs_?
}

build_rpchdrs () {
    # Function to build glibc header files (multilib or not)

    # Arguments are:
    local sys=$1

    local idx

    # This function is also affected by the folloging env vars:
    # LOGFILE
    # NJOBS

    check_numargs build_rpchdrs 1 $# $@

    idx=0
    while [ $idx -lt $dMLSIZE ]; do
	echoV 1 "Installing rpc headers [$idx]"

	if [ ! -e $sys/${aMLDIRS[$idx]}/usr/include/rpc/rpc.h ]; then
	    let LN=$LN+1
	    echoV 1 -n "   $LN install      "
	    cd src_rpcheaders
	    for d in r*; do
		rm -rf $sys/${aMLDIRS[$idx]}/usr/include/$d && \
		cp -rf $d $sys/${aMLDIRS[$idx]}/usr/include \
		    >> $LOGFILE.$LN.glibchdrs-install 2>&1
	    done
	    if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
	    else echoV 1 "...Ok"; fi
	    cd ../
	fi
	
	let idx=$idx+1
    done
}

strip_host () {
    # Arguments are:
    # Installation dir
    local instdir=$1
    # Tools prefix
    local tprefix=$2
    # (optional) exec suffix
    local exe=$3

    check_numargs strip_host 2 $# $@

    echoV 1 "Strip all host executables"

    local STRIPBINS="addr2line ar as c++ c++filt cpp elfedit g++ gcc gfortran gcov gprof ld nm objcopy objdump ranlib readelf size strings strip"
    local STRIPEXEC="cc1 collect2 cc1plus f951 lto-wrapper lto1 install-tools/fixincl"

    for b in $STRIPBINS; do
	# Strip native binaries
        [ -e $instdir/bin/$b${exe} ] && ${tprefix}strip $instdir/bin/$b${exe}
	# Strip cross binaries
        [ -e $instdir/bin/${dTRPTARGET}-$b${exe} ] && ${tprefix}strip $instdir/bin/${dTRPTARGET}-$b${exe}
        [ -e $instdir/${dTRPTARGET}/bin/$b ] && ${tprefix}strip $instdir/${dTRPTARGET}/bin/$b${exe}
    done
    for b in $STRIPEXEC; do
        [ -e $instdir/libexec/gcc/${dTRPTARGET}/*/$b${exe} ] && ${tprefix}strip $instdir/libexec/gcc/${dTRPTARGET}/*/$b${exe}
    done
}

strip_target () {
    # Arguments are:
    # Installation dir
    local instdir=$1

    check_numargs strip_target 1 $# $@

    echoV 1 "Strip all target objects (*.o *.so *.a)"

    local STRIPSOLIBS=`find $instdir \( -name '*.so' -a \! -name libgcc_s.so -a \! -name libpthread.so -a \! -name libc.so \) -type f -printf "%P\n"`
    local STRIPALIBS=`find $instdir \( -name '*.a' -a \! -name libiberty.a -a \! -name libg.a -a \! -name liblto_plugin.dll.a \) -type f -printf "%P\n"`
    local STRIPOBJ=`find $instdir \( -name '*.o' -a \! -name locale_init.o \) -type f -printf "%P\n"`
    local STRIPFLAGS="-R .comment -R .note -R .debug_info -R .debug_aranges -R .debug_pubnames -R .debug_pubtypes -R .debug_abbrev -R .debug_line -R .debug_str -R .debug_ranges -R .debug_loc"
    # For cross builds, we need to add prefix of tools
    local pfx=""
    [ "$dNATIVE" != "Y" ] && pfx=${dTRPTARGET}-

    export PATH="$BUILDINSTDIR/bin:$PATHORIG"

    # remove hardlinks of libc.a and make a copy so that we don't strip off debug info for libg.a
    local LIBCLINKS=`find $instdir \( -name 'libc.a' \) -type f -printf "%P\n"`
    for b in $LIBCLINKS ; do
       cp --remove-destination $instdir/$b  `echo $instdir/$b | sed 's|\(.*\)/.*|\1/libg.a|'`
    done

    for b in $STRIPSOLIBS $STRIPALIBS $STRIPOBJ; do
        ${pfx}objcopy $STRIPFLAGS $instdir/$b || true
    done
}

install_multilib_locale () {
    # Arguments are build sysroot
    local sys=$1

    local MULTILIBLIST=""
    local i18CHARMAPLIST=`ls -1 $sys/usr/share/i18n/charmaps`
    local i18LOCALELIST=`ls -1 $sys/usr/share/i18n/locales`
    local INFOLIST=`ls -1 $sys/usr/share/info`
    local LOCALELIST=`ls -1 $sys/usr/lib/locale`
    local LOCALEFILES="LC_IDENTIFICATION LC_ADDRESS LC_TIME LC_COLLATE LC_MEASUREMENT LC_PAPER LC_MONETARY LC_NUMERIC LC_CTYPE LC_NAME LC_TELEPHONE LC_MESSAGES/SYS_LC_MESSAGES"
    local LOCALECOUNTRIES=`find $sys/usr/share/locale -maxdepth 1 -type d -printf "%P\n"`
    local ZONELIST=`find $sys/usr/share/zoneinfo -type f -printf "%P\n"`

    local d m l f c i z

    echoV 1 "Install multilib locale"

    for d in "${aMLDIRS[@]}"; do
	[ "$d" != "." ] && MULTILIBLIST="$MULTILIBLIST $d"
    done

    cd $sys
    for m in $MULTILIBLIST; do
	for l in $LOCALELIST; do
	    mkdir -p $sys/$m/usr/lib/locale/$l/LC_MESSAGES
	    for f in $LOCALEFILES; do
		rm -f $sys/$m/usr/lib/locale/$l/$f
		ln usr/lib/locale/$l/$f $sys/$m/usr/lib/locale/$l/$f
	    done
	done
    done

    for m in $MULTILIBLIST; do
	rm -rf $sys/$m/usr/include

	cd $sys/$m/etc
	rm -f ./rpc
	ln $sys/etc/rpc ./rpc

	cd $sys/$m/usr/share
	for c in $LOCALECOUNTRIES; do
	    rm -f ./locale/$c/LC_MESSAGES/libc.mo
	    ln $sys/usr/share/locale/$c/LC_MESSAGES/libc.mo ./locale/$c/LC_MESSAGES/libc.mo
	done
	rm -f ./locale/locale.alias
	ln $sys/usr/share/locale/locale.alias ./locale/locale.alias
	for z in $ZONELIST; do
	    rm -f ./zoneinfo/$z
	    ln $sys/usr/share/zoneinfo/$z ./zoneinfo/$z
	done
	for l in $i18LOCALELIST; do
	    rm -f ./i18n/locales/$l
	    ln $sys/usr/share/i18n/locales/$l ./i18n/locales/$l
	done
	for c in $i18CHARMAPLIST; do
	    rm -f ./i18n/charmaps/$c
	    ln $sys/usr/share/i18n/charmaps/$c ./i18n/charmaps/$c
	done
	for i in $INFOLIST; do
	    rm -f ./info/$i
	    ln $sys/usr/share/info/$i ./info/$i
	done
    done
}

GLIBC_SBINlst="ldconfig sln iconvconfig nscd rpcinfo zdump zic"
GLIBC_BINlst="catchsegv gencat getconf getent iconv ldd locale localedef mtrace pcprofiledump rpcgen sprof tzselect xtrace"
GLIBC_LIBEXEClst="POSIX_V7_ILP32_OFF32 POSIX_V7_ILP32_OFFBIG POSIX_V6_ILP32_OFF32 POSIX_V6_ILP32_OFFBIG XBS5_ILP32_OFF32 XBS5_ILP32_OFFBIG"
STRIPFLAGS="-R .comment -R .note -R .debug_info -R .debug_aranges -R .debug_pubnames -R .debug_pubtypes -R .debug_abbrev -R .debug_line -R .debug_str -R .debug_ranges -R .debug_loc"

finish_glibc_install () {
    # Arguments are instdir buildsysroot
    local instdir=$1
    local sys=$2

    local MULTILIBLIST=""
    local d m l LIBLIST b e

    echoV 1 "Finish all glibcs installs"

    for d in "${aMLDIRS[@]}"; do
	[ "$d" != "." ] && MULTILIBLIST="$MULTILIBLIST $d"
    done

    for m in "." $MULTILIBLIST; do
	LIBLIST=`ls -1 $instdir/lib/$m/libgcc*`
	for l in $LIBLIST; do
	    cp -d $l $sys/$m/lib/
	done
	LIBLIST=`ls -1 $instdir/lib/$m/lib*`
	for l in $LIBLIST; do
	    cp -d $l $sys/$m/usr/lib/
	done
    done

    if [ -e $instdir/lib64 ]; then
	LIBLIST=`ls -1 $instdir/lib64/libgcc*`
	for l in $LIBLIST; do
	    cp -d $l $sys/lib64/
	done
	LIBLIST=`ls -1 $instdir/lib64/lib*`
	for l in $LIBLIST; do
	    cp -d $l $sys/usr/lib64/
	done
    fi

    for m in "." $MULTILIBLIST; do
        for b in $GLIBC_SBINlst; do
	    if [ -e $sys/$m/usr/lib/bin/$b ]; then
		${dTRPTARGET}-objcopy $STRIPFLAGS $sys/$m/usr/lib/bin/$b || true
		ln -f $sys/$m/usr/lib/bin/$b $sys/$m/sbin/$b
	    fi
        done
        for b in $GLIBC_BINlst; do
	    if [ "$b" != "catchsegv" -a "$b" != "ldd" -a "$b" != "mtrace" -a "$b" != "tzselect" -a "$b" != "xtrace" ]; then
		${dTRPTARGET}-objcopy $STRIPFLAGS $sys/$m/usr/lib/bin/$b || true
	    fi
            ln -f $sys/$m/usr/lib/bin/$b $sys/$m/usr/bin/$b
        done
        for e in $GLIBC_LIBEXEClst; do
	    if [ -e $sys/$m/usr/lib/bin/$e ]; then
		${dTRPTARGET}-objcopy $STRIPFLAGS $sys/$m/usr/lib/bin/$e || true
		ln -f $sys/$m/usr/lib/bin/$e $sys/$m/usr/libexec/getconf/$e
	    fi
        done
    done
    if [ -e $instdir/lib64 ]; then
        for b in $GLIBC_SBINlst; do
	    if [ -e $sys/usr/lib64/bin/$b ]; then
		${dTRPTARGET}-objcopy $STRIPFLAGS $sys/usr/lib64/bin/$b || true
	    fi
        done
        for b in $GLIBC_BINlst; do
	    if [ "$b" != "catchsegv" -a "$b" != "ldd" -a "$b" != "mtrace" -a "$b" != "tzselect" -a "$b" != "xtrace" ]; then
		${dTRPTARGET}-objcopy $STRIPFLAGS $sys/usr/lib64/bin/$b || true
	    fi
        done
        for e in $GLIBC_LIBEXEClst; do
	    if [ -e $sys/usr/lib64/bin/$e ]; then
		${dTRPTARGET}-objcopy $STRIPFLAGS $sys/usr/lib64/bin/$e || true
	    fi
        done
    fi
    
    for b in $GLIBC_SBINlst; do
	rm -f $sys/sbin/$b
    done
    for b in $GLIBC_BINlst; do
	rm -f $sys/usr/bin/$b
    done
    for e in $GLIBC_LIBEXEClst; do
	rm -f $sys/usr/libexec/getconf/$e
    done
}

build_cross_glibc () {
    # Build a cross glibc with sysroot

    # Arguments are:
    # Target triplet
    local TGT=$1
    # Sysroot dir
    local sys=$2
    # (optional) Extra config options
    local cfgoptions=$3
    local docsdir=$sys/share/docs

    local idx t dirsrc dirdst f

    check_numargs build_cross_glibc 2 $# $@

    local MINOPTS="$CROSS_GLIBC_CONFIG \
	--build=$(src_glibc/scripts/config.guess) \
        --with-headers=$sys/usr/include"

    idx=0
    while [ $idx -lt $dMLSIZE ]; do
	echoV 1 "Building cross glibc with sysroot [$idx]"

	t=${aMLTARGET[$idx]}
	if [ "$t" = "" ]; then
	    t=$TGT
	fi
	let LN=$LN+1

	prepare_objdir obj_glibc_$idx src_glibc/
	CONFIGENV="BUILD_CC=gcc CC=\"$TGT-gcc ${aMLCFLAGS[$idx]}\" \
	    CXX=\"$TGT-g++ ${aMLCFLAGS[$idx]}\" $dLIBBUILD \
	    AR=$TGT-ar RANLIB=$TGT-ranlib"
	BUILDENV="$dLIBBUILD"
	build_cbi \
	    "../obj_glibc_$idx" \
	    "$MINOPTS --host=$t ${aMLCONFIG[$idx]} $cfgoptions" \
	    "all" \
	    "install install_root=$sys/${aMLDIRS[$idx]}"
	
	[ "$STP" != "" ] && return
	mkdir -p $sys/${aMLDIRS[$idx]}/usr/lib/${aMLOSDIRS[$idx]}/bin
	dirsrc=$sys/${aMLDIRS[$idx]}
	dirdst=$sys/${aMLDIRS[$idx]}/usr/lib/${aMLOSDIRS[$idx]}/bin
	for f in $GLIBC_SBINlst; do
	    [ -e $dirsrc/sbin/$f ] && cp -f $dirsrc/sbin/$f $dirdst
	    [ -e $dirsrc/usr/sbin/$f ] && cp -f $dirsrc/usr/sbin/$f $dirdst
	done
	for f in $GLIBC_BINlst; do
	    [ -e $dirsrc/usr/bin/$f ] && cp -f $dirsrc/usr/bin/$f $dirdst
	done
	for f in $GLIBC_LIBEXEClst; do
	    [ -e $dirsrc/usr/libexec/getconf/$f ] && cp -f $dirsrc/usr/libexec/getconf/$f $dirdst
	done
	
	cd ../
	let idx=$idx+1
    done
    #timezone data for eglibc > 2.15
    if [ $(echo $EGLIBC_VER 2.15 | awk '{if ($1 > $2) print 1; else print 0}') -eq 1 ]; then
        let LN=$LN+1
        echoV 1 -n "   $LN install tzdata "
        build_tzdata $sys 0
        if [ $? != 0 ]; then echoV 1 ".Error"; cd ../; STP=1; return
        else echoV 1 ".Ok"; fi
    fi
    cd obj_glibc_0_scratch
    let LN=$LN+1
    mkdir -p $docsdir/html $docsdir/pdf
    echoV 1 -n "   $LN install html "
    make html >> $LOGFILE.$LN.glibc-docs 2>&1
    if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
    else echoV 1 "...Ok"; fi
    cp -r ../obj_glibc_0_scratch/manual/libc $docsdir/html/libc
    let LN=$LN+1
    echoV 1 -n "   $LN install pdf  "
    make pdf  >> $LOGFILE.$LN.glibc-docs 2>&1
    if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
    else echoV 1 "...Ok"; fi
    cp ../obj_glibc_0_scratch/manual/libc.pdf $docsdir/pdf/libc.pdf
    cd ../
    CONFIGENV=""
    BUILDENV=""
    remove_objdir obj_glibc_?
}

build_tzdata () {
    # Build timezone data for eglibc > 2.15
    local sys=$1
    local native=$2

    prepare_objdir obj_tzdata src_tzdata
    cd ../obj_tzdata
    cat > nsswitch.conf << "EOF"
# Begin /etc/nsswitch.conf

passwd: files
group: files
shadow: files

hosts: files dns
networks: files

protocols: files
services: files
ethers: files
rpc: files

# End /etc/nsswitch.conf
EOF
    cp -f nsswitch.conf ../obj_glibc_0/nss/

    local zic_cmd=../obj_glibc_0_scratch/timezone/cross-zic
    if [ $native -eq 1 ]; then
        zic_cmd=../obj_glibc_0_scratch/timezone/zic
    fi
    ZONEINFO=$sys/usr/share/zoneinfo
    mkdir -p $ZONEINFO/{posix,right}

    for tz in etcetera southamerica northamerica europe africa antarctica  \
              asia australasia backward pacificnew systemv; do
        $zic_cmd -L /dev/null   -d $ZONEINFO       -y "sh yearistype.sh" ${tz} >> $LOGFILE.$LN.glibc-tzdata 2>&1
        $zic_cmd -L /dev/null   -d $ZONEINFO/posix -y "sh yearistype.sh" ${tz} >> $LOGFILE.$LN.glibc-tzdata 2>&1
        $zic_cmd -L leapseconds -d $ZONEINFO/right -y "sh yearistype.sh" ${tz} >> $LOGFILE.$LN.glibc-tzdata 2>&1
    done

    cp -f zone.tab zone1970.tab iso3166.tab $ZONEINFO >> $LOGFILE.$LN.glibc-tzdata 2>&1
    $zic_cmd -d $ZONEINFO -p America/New_York >> $LOGFILE.$LN.glibc-tzdata 2>&1
    if [ -e $sys/nof ]; then
        cp -R $sys/usr/share/zoneinfo $sys/nof/usr/share/
    fi
    unset ZONEINFO
    cd ../
    remove_objdir obj_tzdata_?
}

build_cross_rpc () {
    # Build a cross rpc with sysroot

    # Arguments are:
    # Target triplet
    local TGT=$1
    # Sysroot dir
    local sys=$2

    local idx t

    check_numargs build_cross_rpc 2 $# $@

    idx=0
    while [ $idx -lt $dMLSIZE ]; do
	echoV 1 "Building cross rpc with sysroot [$idx]"

	t=${aMLTARGET[$idx]}
	if [ "$t" = "" ]; then
	    t=$TGT
	fi
	let LN=$LN+1

	prepare_objdir obj_rpc_$idx src_libtirpc/
	cd ../obj_rpc_$idx
	CONFIGENV="BUILD_CC=gcc CC=\"$TGT-gcc ${aMLCFLAGS[$idx]}\" \
	    CXX=\"$TGT-g++ ${aMLCFLAGS[$idx]}\" CFLAGS=\"-fPIC -O3\" \
	    AR=$TGT-ar RANLIB=$TGT-ranlib"
	build_cbi \
	    "../obj_rpc_$idx" \
	    "--host=$t --prefix=/usr --with-sysroot=$sys --libdir=/${aMLDIRS[$idx]}/usr/lib/${aMLOSDIRS[$idx]}" \
	    "all" \
	    "install DESTDIR=$sys"
	
	[ "$STP" != "" ] && return
	
	cd ../
	let idx=$idx+1
    done
    CONFIGENV=""
    remove_objdir obj_rpc_?
}

build_native_glibc () {
    # Build a native glibc

    # Arguments are:
    # Target triplet
    local TGT=$1
    # Instalal dir (gcc)
    local instdir=$2
    # Instalal dir (glibc)
    local instlibdir=$3
    # (optional) Extra config options
    local cfgoptions=$4
    local docsdir=$instlibdir/share/docs

    local idx t f

    check_numargs build_native_glibc 3 $# $@

    local MINOPTS="--prefix=/usr \
        --build=$(src_glibc/scripts/config.guess) \
        --disable-profile --without-gd --without-cvs --disable-nls \
        libc_cv_forced_unwind=yes libc_cv_c_cleanup=yes libc_cv_ppc_machine=yes"

    idx=0
    while [ $idx -lt $dMLSIZE ]; do
	echoV 1 "Building native glibc [$idx]"

	t=${aMLTARGET[$idx]}
	if [ "$t" = "" ]; then
	    t=$TGT
	fi
	let LN=$LN+1

	prepare_objdir obj_glibc_$idx src_glibc/
	CONFIGENV="BUILD_CC=\"${dTBUILD}gcc\" \
            CC=\"$instdir/bin/gcc ${aMLCFLAGS[$idx]}\" \
            CXX=\"$instdir/bin/g++ ${aMLCFLAGS[$idx]}\" \
            AR=\"$instdir/bin/ar\" RANLIB=\"$instdir/bin/ranlib\""
	build_cbi \
	    "../obj_glibc_$idx" \
	    "$MINOPTS --host=$t ${aMLCONFIG[$idx]} $cfgoptions" \
	    "all" \
	    "install install_root=$instlibdir/${aMLDIRS[$idx]}"

	[ "$STP" != "" ] && return
	mkdir -p $instlibdir/${aMLDIRS[$idx]}/usr/lib/${aMLOSDIRS[$idx]}/bin
	for f in $GLIBC_SBINlst; do
	    [ -e $instlibdir/${aMLDIRS[$idx]}/sbin/$f ] && cp -f $instlibdir/${aMLDIRS[$idx]}/sbin/$f $instlibdir/usr/lib/${aMLOSDIRS[$idx]}/bin
	    [ -e $instlibdir/${aMLDIRS[$idx]}/usr/sbin/$f ] && cp -f $instlibdir/${aMLDIRS[$idx]}/usr/sbin/$f $instlibdir/usr/lib/${aMLOSDIRS[$idx]}/bin
	done
	for f in $GLIBC_BINlst; do
	    [ -e $instlibdir/${aMLDIRS[$idx]}/usr/bin/$f ] && cp -f $instlibdir/${aMLDIRS[$idx]}/usr/bin/$f $instlibdir/usr/lib/${aMLOSDIRS[$idx]}/bin
	done

	cd ../
	let LN=$LN+4
	let idx=$idx+1
    done
    #timezone data for eglibc > 2.15
    if [ $(echo $EGLIBC_VER 2.15 | awk '{if ($1 > $2) print 1; else print 0}') -eq 1 ]; then
        let LN=$LN+1
        echoV 1 -n "   $LN install tzdata "
        build_tzdata $instlibdir 1
        if [ $? != 0 ]; then echoV 1 ".Error"; cd ../; STP=1; return
        else echoV 1 ".Ok"; fi
    fi
    cd obj_glibc_0_scratch
    let LN=$LN+1
    mkdir -p $docsdir/html $docsdir/pdf
    echoV 1 -n "   $LN install html "
    make html >> $LOGFILE.$LN.glibc-docs 2>&1
    if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
    else echoV 1 "...Ok"; fi
    cp -r ../obj_glibc_0_scratch/manual/libc $docsdir/html/libc
    let LN=$LN+1
    echoV 1 -n "   $LN install pdf  "
    make pdf  >> $LOGFILE.$LN.glibc-docs 2>&1
    if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
    else echoV 1 "...Ok"; fi
    cp ../obj_glibc_0_scratch/manual/libc.pdf $docsdir/pdf/libc.pdf
    cd ../
    CONFIGENV=""
    remove_objdir obj_glibc_?
}

build_native_rpc () {
    # Build a native rpc

    # Arguments are:
    # Target triplet
    local TGT=$1
    # Instalal dir (gcc)
    local instdir=$2
    # Instalal dir (glibc)
    local instlibdir=$3

    local idx t

    check_numargs build_native_rpc 3 $# $@

    idx=0
    while [ $idx -lt $dMLSIZE ]; do
	echoV 1 "Building native rpc [$idx]"

	t=${aMLTARGET[$idx]}
	if [ "$t" = "" ]; then
	    t=$TGT
	fi
	let LN=$LN+1

	prepare_objdir obj_rpc_$idx src_libtirpc/
	cd ../obj_rpc_$idx
	CONFIGENV="BUILD_CC=\"${dTBUILD}gcc\" CFLAGS=\"-fPIC -O3\" \
            CC=\"$instdir/bin/gcc ${aMLCFLAGS[$idx]}\" \
            CXX=\"$instdir/bin/g++ ${aMLCFLAGS[$idx]}\" \
            AR=\"$instdir/bin/ar\" RANLIB=\"$instdir/bin/ranlib\""
	build_cbi \
	    "../obj_rpc_$idx" \
	    "--host=$t --prefix=/usr --with-sysroot=$instlibdir --libdir=/${aMLDIRS[$idx]}/usr/lib/${aMLOSDIRS[$idx]}" \
	    "all" \
	    "install DESTDIR=$instlibdir"

	[ "$STP" != "" ] && return

	cd ../
	let idx=$idx+1
    done
    CONFIGENV=""
    remove_objdir obj_rpc_?
}

build_native_locale () {
    # Build a native locale

    # Arguments are:
    # Target triplet
    local TGT=$1
    # Instalal dir (gcc)
    local instdir=$2
    # Instalal dir (glibc)
    local instlibdir=$3

    local BUILDDIR=`pwd`

    check_numargs build_native_locale 3 $# $@

    prepare_objdir obj_loc

    echoV 1 "Building native localedef"
    CONFIGENV="BUILD_CC=\"${dTBUILD}gcc\" \
        CC=\"$instdir/bin/gcc\" CXX=\"$instdir/bin/g++\" \
        AR=\"$instdir/bin/ar\" RANLIB=\"$instdir/bin/ranlib\""
    INSTALLENV="eval"
    build_cbi \
        "../src_localedef" \
        "--prefix=/usr --with-glibc=$BUILDDIR/obj_glibc_0" \
        "all" \
        "install_roots=$instlibdir '\"LOCALEDEF_OPTS=--big-endian --uint32-align=4\"' install-locales"
    cd ../
    INSTALLENV=""
    CONFIGENV=""

    remove_objdir obj_loc
}

build_cross_locale () {
    # Build a cross locale

    # Arguments are:
    # Target triplet
    local TGT=$1
    # Used in cross compilation
    local INSTROOT=$2

    local BUILDDIR=`pwd`
    local GLIBCDIR=$BUILDDIR/obj_glibc_0

    check_numargs build_cross_locale 2 $# $@

    prepare_objdir obj_loc

    echoV 1 "Building cross localedef"
    INSTALLENV="eval"
    build_cbi \
        "../src_localedef" \
        "--prefix=/usr --with-glibc=$GLIBCDIR" \
        "all" \
        "$INSTROOT '\"LOCALEDEF_OPTS=--big-endian --uint32-align=4\"' install-locales"
    cd ../
    INSTALLENV=""

    remove_objdir obj_loc
}

build_newlib () {
    # Function to build eabi newlib

    # Arguments are:
    # Target triplet
    local tgt=$1
    # (optional) Extra config options
    local cfgoptions=$2
    local docsdir=$EBUILDSYSROOT/share/docs

    check_numargs build_newlib 1 $# $@

    echoV 1 "Building eabi newlib"
    mkdir -p $docsdir/html $docsdir/pdf
    local MINOPTS="--enable-newlib-io-long-long \
	--disable-newlib-multithread --disable-nls"
    prepare_objdir obj_newlib
    build_cbi \
	"../src_newlib" \
	"--prefix=$TOOLINSTDIR --target=$tgt $MINOPTS $cfgoptions" \
	"" \
	"install prefix=$BUILDINSTDIR install_root=$BUILDINSTDIR/$tgt htmldir=$docsdir/html pdfdir=$docsdir/pdf infodir=$docsdir/info mandir=$docsdir/man"
    let LN=$LN+1
    echoV 1 -n "   $LN install html "
    make html >> $LOGFILE.$LN.install 2>&1
    if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
    else echoV 1 "...Ok"; fi
    cp -r $tgt/newlib/libc/libc.html $docsdir/html/libc
    cp -r $tgt/newlib/libm/libm.html $docsdir/html/libm

    let LN=$LN+1
    echoV 1 -n "   $LN install pdf  "
    make pdf >> $LOGFILE.$LN.install 2>&1
    if [ $? != 0 ]; then echoV 1 "...Error"; cd ../; STP=1; return
    else echoV 1 "...Ok"; fi
    cp $tgt/newlib/libc/libc.pdf $docsdir/pdf/libc.pdf
    cp $tgt/newlib/libm/libm.pdf $docsdir/pdf/libm.pdf

    cd ../
    remove_objdir obj_newlib
}

build_newlib_nano () {
    # Function to build eabi NewLib nano version

    # Arguments are:
    # Target triplet
    local tgt=$1
    # (optional) Extra config options
    local cfgoptions=$2
    local docsdir=$EBUILDSYSROOT/share/docs

    check_numargs build_newlib 1 $# $@

    echoV 1 "Building eabi newlib nano"
    mkdir -p $docsdir/html $docsdir/pdf
    local MINOPTS="--enable-newlib-io-long-long \
	--disable-newlib-multithread --disable-nls"
    prepare_objdir obj_newlib
    build_cbi \
	"../src_newlib" \
	"--prefix=$TOOLINSTDIR --target=$tgt $MINOPTS $cfgoptions" \
	"" \
	"install prefix=$BUILDINSTDIR install_root=$BUILDINSTDIR/$tgt htmldir=$docsdir/html pdfdir=$docsdir/pdf infodir=$docsdir/info mandir=$docsdir/man"
    
    cd ../
    remove_objdir obj_newlib
}

test_newlib () {
    # Function to build eabi newlib

    check_numargs test_newlib 0 $# $@

    local i m

    if [ ! -d obj_newlib ]; then
	echoV 0 "No object directory to test"
	return
    fi
    if [ "$DGDESC" = "" ]; then
	echoV 0 "No DGDESC is set. Use command t=<..>"
	return
    fi

    echoV 1 "Running newlib dejagnu"

    cd obj_newlib
    make $NJOBS -k check-target-newlib \
	RUNTESTFLAGS="$TESTFLAGS $dBRDRUNTESTFLAGS --target_board=bm_board" > $LOGFILE.$LN.newlib_tests 2>&1
    cd ../
}

test_glibc () { # Function to run glibc tests

    local objdir

    if [ ! -d obj_glibc_scratch -a ! -d obj_glibc_0_scratch ]; then
	echoV 0 "No object directory to test"
	return
    fi

    if [ "$DGDESC" = "" ]; then
	echoV 0 "No DGDESC is set. Use command t=<..>"
	return
    fi

    echoV 1 "Running glibc tests"
    for objdir in obj_glibc_*scratch; do
	echoV 1 -n "   $LN multilib [${objdir:4}]  "
	cd $objdir

	# Host machine
	local host
	# Script for remote connections
	local script

	host="$dBRDHOSTNAME"
	script="${PWD%/*}/${objdir%_scratch}/scripts/cross-test-ssh.sh"

	if [ "$host" == 0 ]; then
		echoV 0 "No host name set"
		return
	fi

	if [ ! -s $script ]; then
		echoV 0 "No script set for remote connections"
		return
	fi

	make "cross-test-wrapper=$script ${USER}@$host" -k check > $LOGFILE.$LN.${objdir:4} 2>&1
	if [ $? != 0 ]; then echoV 1 "...Error"; else echoV 1 "...Ok"; fi
	cd ../
    done
}

fix_bmspec () {
    # Function to change spec file to set built dynamic linker

    # Arguments are:
    # Target triplet
    local TGT=$1
    # Instalal dir
    local instdir=$2
    # Bare metal support
    local BMDIR=$3
    
    check_numargs fix_bmspec 3 $# $@

    local c1 ci cn sysr32 sysr64 gccfile specdir x

    echoV 1 "Fixing specs file for bare metal           "
    gccfile=`$instdir/bin/$TGT-gcc -print-libgcc-file-name`
    specdir=`dirname $gccfile`

    echoV 1 -n -e "   Installing bare metal support files "
    cp -f $BMDIR/bin/libos/head32.o $specdir/bmcrti.o   ; if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return; fi
    cp -f $BMDIR/bin/libos/tail32.o $specdir/bmcrtn.o   ; if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return; fi
    cp -f $BMDIR/bin/libos/head64.o $specdir/64/bmcrti.o; if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return; fi
    cp -f $BMDIR/bin/libos/tail64.o $specdir/64/bmcrtn.o; if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return; fi
    cp -f $BMDIR/bin/libos32.a $specdir/libbm.a         ; if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return; fi
    cp -f $BMDIR/bin/libos64.a $specdir/64/libbm.a      ; if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return; fi
    cp -f $BMDIR/bm_app32.lds $specdir/bm32.lds         ; if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return; fi
    cp -f $BMDIR/bm_app64.lds $specdir/bm64.lds         ; if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return; fi
    echoV 1 "...Ok"

    echoV 1 -n -e "   Fixing bare metal start files     "
    rm -f $specdir/specs
    $instdir/bin/$TGT-gcc -dumpspecs > $LOGFILE.$LN.specs 2>&1

    cat > spec.awk <<EOF
{
  if (sfound == 1) {
    print gensub("%{","%{Xvrtuboot : %(startfile_vrtuboot) ; ","g")
  } else if (efound == 1) {
    print gensub("%{","%{Xvrtuboot : %(endfile_vrtuboot) ; ","g")
  } else print gensub("SPECDIR",sd,"g")
  sfound=0; efound=0
}
/^*startfile:$/ { sfound=1 }
/^*endfile:$/   { efound=1 }
EOF

    cp -f $LOGFILE.$LN.specs $LOGFILE.$LN.specs2
    cat >> $LOGFILE.$LN.specs2 <<EOF
*startfile_vrtuboot:
%{m32:-m elf32ppc -TSPECDIR/bm32.lds} %{m64:-m elf64ppc -TSPECDIR/bm64.lds} %{!m32:%{!m64:-m elf32ppc -TSPECDIR/bm32.lds}} bmcrti.o%s ecrti.o%s crtbegin.o%s libbm.a%s

*endfile_vrtuboot:
crtend.o%s ecrtn.o%s bmcrtn.o%s
EOF

    cat $LOGFILE.$LN.specs2 | awk -f spec.awk sd="$specdir" > $LOGFILE.$LN.specs-new
    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return;
    else echoV 1 "...Ok"; fi
    rm -f spec.awk

    cp -f $LOGFILE.$LN.specs-new $specdir/specs

    echoV 1 -n -e "   Checking installation of new specs file   "
    x=`$instdir/bin/$TGT-gcc -v 2>&1 | head -n 1 | grep 'Reading specs from'`
    if [ "$x" = "" ]; then echoV 1 "...Error"; STP=1; return;
    else echoV 1 "...Ok"; fi

    if [ -d obj_gcc ]; then
	echoV 1 "Fixing spec file on build directory"
	cp -f $LOGFILE.$LN.specs-new obj_gcc/gcc/specs
    fi
}

fix_spec () {
    # Function to change spec file to set built dynamic linker

    # Arguments are:
    # Target triplet
    local TGT=$1
    # Instalal dir
    local instdir=$2
    # Build sysroot
    local Bsys=$3
    # Tool sysroot
    local Tsys=$4
    # Optional argument
    local LDIR2=$5
    
    check_numargs fix_spec 4 $# $@

    local c1 ci cn sysr32 sysr64 sysrnof gccfile specdir x

    echoV 1 "Fixing specs file"

    if [ "$LDIR2" = "" ]; then
	# This is native build
	GCCBIN=$instdir/bin/gcc
    else
	GCCBIN=$instdir/bin/$TGT-gcc
    fi

    gccfile=`$GCCBIN -print-libgcc-file-name`
    specdir=`dirname $gccfile`
    rm -f $specdir/specs

    echoV 1 -n -e "   Replacing dyn linker                        "
    $GCCBIN -dumpspecs > $LOGFILE.$LN.specs 2>&1

    if [ -e $Bsys/lib64/ld-linux-x86-64.so.2 ]; then
        # x86_64
	cat > spec.awk <<EOF
{
  if (lfound == 1) {
    print gensub("/lib64/ld-linux-x86-64.so.2",sysr64,"g")
  } else print \$0
  lfound=0
}
/^*link:$/            { lfound=1 }
EOF
	sysr64="$Tsys/lib64/ld-linux-x86-64.so.2 -rpath $Tsys/lib64 -L$Tsys/lib64"
	[ "$LDIR2" != "" ] && sysr64="$sysr64 -rpath $LDIR2/lib -L$LDIR2/lib"
 
    elif [ -e $Bsys/lib64/ld64.so.1 ]; then
        # ppc 64
	cat > spec.awk <<EOF
{
  if (lfound == 1) {
    print "%{!m64: %{!msoft-float:%(link_os_linux_spec32)}%{msoft-float:%(link_os_linux_specnof)}}%{m64:%(link_os_linux_spec64)}"
  } else if (l64found == 1) {
    print gensub("/lib64/ld64.so.1",sysr64,"g")
  } else if (l32found == 1) {
    print gensub("/lib/ld.so.1",sysr32,"g")
    print ""
    print "*link_os_linux_specnof:"
    print gensub("/lib/ld.so.1",sysrnof,"g")
  } else print \$0
  l32found=0; l64found=0
  lfound=0
}
/^*link_os_linux:$/   { lfound=1 }
/^*link_os_linux_spec32:$/   { l32found=1 }
/^*link_os_linux_spec64:$/   { l64found=1 }
EOF
	sysr32="$Tsys/lib/ld.so.1 -rpath $Tsys/lib -L$Tsys/lib -rpath $Tsys/usr/lib"
	[ "$LDIR2" != "" ] && sysr32="$sysr32 -rpath $LDIR2/lib -L$LDIR2/lib"
	sysr64="$Tsys/lib64/ld64.so.1 -rpath $Tsys/lib64 -L$Tsys/lib64 -rpath $Tsys/usr/lib64"
	[ "$LDIR2" != "" ] && sysr64="$sysr64 -rpath $LDIR2/lib64 -L$LDIR2/lib64"
	sysrnof="$Tsys/nof/lib/ld.so.1 -rpath $Tsys/nof/lib -L$Tsys/nof/lib -rpath $Tsys/nof/usr/lib"
	[ "$LDIR2" != "" ] && sysrnof="$sysrnof -rpath $LDIR2/lib/nof -L$LDIR2/lib/nof"

    elif [ -e $Bsys/lib/ld.so.1 ]; then
        # ppc 32
	if [ "$dUSESYS" = "Y" ]; then
	    cat > spec.awk <<EOF
{
  if (lfound == 1) {
    print gensub("/lib/ld.so.1",sysr32,"g")
  } else if (sfound == 1) {
    print gensub("crt1.o%s}",c1,"g",gensub("crti.o%s",ci,"g"))
  } else if (efound == 1) {
    print gensub("crtn.o%s",cn,"g")
  } else if (l64found == 1) {
    print gensub("/lib64/ld64.so.1",sysr64,"g")
  } else if (l32found == 1) {
    print gensub("/lib/ld.so.1",sysr32,"g")
  } else print \$0
  l32found=0; l64found=0
  lfound=0; sfound=0; efound=0
}
/^*link_os_linux:$/   { lfound=1 }
/^*startfile_linux:$/ { sfound=1 }
/^*endfile_linux:$/   { efound=1 }
/^*link_os_linux_spec32:$/   { l32found=1 }
/^*link_os_linux_spec64:$/   { l64found=1 }
EOF
            c1="$Tsys/usr/lib/crt1.o%s}"
	    ci="$Tsys/usr/lib/crti.o%s"
	    cn="$Tsys/usr/lib/crtn.o%s"
	else
	    cat > spec.awk <<EOF
{
  if (lfound == 1) {
    print "%{!msoft-float:%(link_os_linux_spec32)}%{msoft-float:%(link_os_linux_specnof)}"
    print ""
    print "*link_os_linux_spec32:"
    print gensub("/lib/ld.so.1",sysr32,"g")
    print ""
    print "*link_os_linux_specnof:"
    print gensub("/lib/ld.so.1",sysrnof,"g")
  } else print \$0
  lfound=0
}
/^*link_os_linux:$/   { lfound=1 }
EOF
	fi
	sysr32="$Tsys/lib/ld.so.1 -rpath $Tsys/lib -L$Tsys/lib -rpath $Tsys/usr/lib"
	[ "$LDIR2" != "" ] && sysr32="$sysr32 -rpath $LDIR2/lib -L$LDIR2/lib"
	sysrnof="$Tsys/nof/lib/ld.so.1 -rpath $Tsys/nof/lib -L$Tsys/nof/lib -rpath $Tsys/nof/usr/lib"
	[ "$LDIR2" != "" ] && sysrnof="$sysrnof -rpath $LDIR2/lib/nof -L$LDIR2/lib/nof"

    elif [ -e $Bsys/lib/ld-linux.so.2 ]; then
        # i686
	cat > spec.awk <<EOF
{
  if (lfound == 1) {
    print gensub("/lib/ld-linux.so.2",sysr32,"g")
  } else print \$0
  lfound=0
}
/^*dynamic_linker:$/  { lfound=1 }
EOF
	sysr32="$Tsys/lib/ld-linux.so.2 -rpath $Tsys/lib -L$Tsys/lib"
        [ "$LDIR2" != "" ] && sysr32="$sysr32 -rpath $LDIR2/lib -L$LDIR2/lib"

    else
        echoV 0 "[fix_spec] Cannot find dynamic linker"
        build_exit 1
    fi

    cat $LOGFILE.$LN.specs | awk -f spec.awk sysr32="$sysr32" sysr64="$sysr64" \
	sysrnof="$sysrnof" c1="$c1" ci="$ci" cn="$cn" > $LOGFILE.$LN.specs-new
    if [ $? != 0 ]; then echoV 1 "...Error"; STP=1; return;
    else echoV 1 "...Ok"; fi
    rm -f spec.awk

    cp -f $LOGFILE.$LN.specs-new $specdir/specs

    echoV 1 -n -e "   Checking instalation of new specs file      "
    x=`$GCCBIN -v 2>&1 | head -n 1 | grep 'Reading specs from'`
    if [ "$x" = "" ]; then echoV 1 "...Error"; STP=1; return;
    else echoV 1 "...Ok"; fi
}

fix_links () {
    # Function to create links to the tools to bypass "TGT-" prefix

    # Arguments are:
    # Target triplet
    local TGT=$1
    # Instalal dir
    local instdir=$2
    # Optional new TGT- prefix
    local NEWTGT=$3

    check_numargs fix_links 2 $# $@

    echoV 1 "Creating soft links"
    pushd $instdir > /dev/null
    cd bin
    for f in addr2line ar as c++ c++filt cpp g++ gcc gcc-4.4.0 gccbug gcov gfortran \
	gprof ld nm objcopy objdump ranlib readelf size strings strip; do
        [ -L $f ] && rm -f $f
	if [ -f ${TGT}-$f -a ! -f $f ]; then
	    echoV 1 "   Creating link: $f"
	    ln -s ${TGT}-$f ${NEWTGT}$f
	fi
    done
    popd > /dev/null
}    

check_sequence () {
    # Function to check if the execution steps are in coherent order. Also set LN globally

    # Arguments are:
    # Start LN number (global var)
    LN=$1
    # Current sequence number
    local seq=$2

    # This function uses and sets the folloging global var:
    # LASTSEQ

    check_numargs check_sequence 2 $# $@

    if [ $seq -lt $LASTSEQ ]; then
	echoV 0 "[check_sequence] Invalid sequence on execution steps. this:$seq last:$LASTSEQ"
	build_exit 1
    fi
    LASTSEQ=$seq
}

execute_job () {
    # Function to execute one job

    # Arguments are:
    # Job descriptor
    local j=$1
    shift
    # List of steps to execute

    local lst

    STP=""
    LASTSEQ=0
    for s in $*; do
	if [ "$STP" != "" ]; then
	    # Some error happened, stop execution of this job
	    return
	fi
	STP=""
	echoV 2 "Executing step $s"
	case $s in
	    chk)
                check_sequence 100 5
		if check_versions "0 2 4   8 10 12 14 16 18 20 22 24 26 28 34 36"; then
		    return
		fi
		;;
	    dst)
                check_sequence 100 10
		echoV 1 "Starting job from scratch"
		cd ../
		rm -rf $BUILDINSTDIR $LOGFILE.* $j
		mkdir -p $j/logs
		cd $j
		;;
	    rm)
                check_sequence 100 15
                # Remove installed directory
                rm -rf $BUILDINSTDIR $LOGFILE.*
                ;;
            src)
                check_sequence 100 20
	        # Pass build data to gcc -v"
		if [ "$flgREV" = "" ]; then
		    # Add revision number, so we can reproduce exactly"
		    echo `date` "        build.sh rev=$BLDrevnum $INVOKED" > $LOGFILE.dev_phase
		else
		    # Invocation already has a revision number, copy it as is"
		    echo `date` "        build.sh $INVOKED" > $LOGFILE.dev_phase
		fi
		get_sources $dLSTSOURCES
	        ;;
	    intgr)
	        check_sequence 100 21
		integrate_libraries
	        ;;
	    gitIntgr)
	        #Apply sources from GIT repository
	        intergrate_sources_from_git
	        ;;
	    gmp)
                check_sequence 110 22
	        # Build gmp libraries
		export PATH=$PATHORIG
		build_lib gmp $HOSTLIBINST/usr \
		    "--disable-shared --disable-nls" \
		    "$dGMPCONFIG32" \
		    "$dGMPCONFIG64"
	        ;;
	    Ngmp)
		check_sequence 110 22
                # Build gmp libraries
		export PATH=$PATHORIG
		build_lib gmp $HOSTLIBINST/usr \
		    "--disable-nls" \
		    "$dGMPCONFIG32" \
		    "$dGMPCONFIG64"
		;;
            Tgmp)
                check_sequence 120 23
                # Build gmp libraries
		export PATH=$PATHORIG
		build_lib gmp $HOSTLIBINST/tgmp \
                    "--disable-nls" \
		    "$dTGMPCONFIG32" \
                    "$dTGMPCONFIG64"
		;;
	    mpfr)
                check_sequence 130 24
	        # Build mpfr libraries
		export PATH=$PATHORIG
		build_lib mpfr $HOSTLIBINST/usr \
                    "--disable-shared --disable-nls" \
		    "--with-gmp=$HOSTLIBINST/usr" \
                    "--with-gmp=$HOSTLIBINST/usr/64"
	        ;;
	    mpc)
                check_sequence 140 25
	        # Build mpc libraries
		export PATH=$PATHORIG
		build_lib mpc $HOSTLIBINST/usr \
                    "--disable-shared --disable-nls" \
		    "--with-gmp=$HOSTLIBINST/usr --with-mpfr=$HOSTLIBINST/usr" \
                    "--with-gmp=$HOSTLIBINST/usr/64 --with-mpfr=$HOSTLIBINST/usr/64"
	        ;;
	    expat)
                check_sequence 160 27
	        # Build expat libraries
		export PATH=$PATHORIG
		build_lib expat $HOSTLIBINST/usr \
                    "--disable-shared --disable-nls" \
                    "" \
                    ""
	        ;;
	    cloog)
                check_sequence 150 26
	        # Build cloog libraries
		export PATH=$PATHORIG
		if [ -e src_isl ]; then
		    build_lib isl $HOSTLIBINST/usr \
			"--disable-shared --disable-nls" \
			"--with-gmp=system --with-gmp-prefix=$HOSTLIBINST/usr" \
			"--with-gmp=system --with-gmp-prefix=$HOSTLIBINST/usr/64"
		    touch x.c
		    ${dTBUILD}gcc -c x.c
		    x=`file x.o | grep 64-bit`
		    rm -f x.c x.o
		    if [ "$x" != "" ]; then x="/64"; fi
		    WITHISL="--with-isl=$HOSTLIBINST/usr$x"
		else
		    WITHISL=""
		fi
		build_lib cloog $HOSTLIBINST/usr \
		    "--disable-shared --disable-nls $WITHISL" \
		    "$dCLOOGCONFIG32 --with-gmp=system --with-gmp-prefix=$HOSTLIBINST/usr" \
		    "$dCLOOGCONFIG64 --with-gmp=system --with-gmp-prefix=$HOSTLIBINST/usr/64"
	        ;;
	    Xbin)
                check_sequence 200 28
	        # Build cross binutils
		export PATH=$PATHORIG
		build_bin $dTRPTARGET $TOOLINSTDIR \
                    "--with-sysroot=$TOOLSYSROOT $dBINCONFIG" "prefix=$BUILDINSTDIR" \
		    "" $BUILDSYSROOT/share/docs
	        ;;
	    sXbin)
                check_sequence 200 28
	        # Build cross binutils
		export PATH=$PATHORIG
		build_bin $dTRPTARGET $TOOLINSTDIR \
                    "--with-sysroot=$TOOLSYSROOT $dBINCONFIG" "prefix=$BUILDINSTDIR" \
		    "LDFLAGS=--static" $BUILDSYSROOT/share/docs
	        ;;
	    Ebin)
                check_sequence 200 28
	        # Build cross binutils
		export PATH=$PATHORIG
		build_bin $dTRPTARGET $TOOLINSTDIR \
		    "--with-sysroot=$ETOOLSYSROOT --disable-nls $dBINCONFIG" "prefix=$BUILDINSTDIR" \
		    "" $EBUILDSYSROOT/share/docs
	        ;;
	    sEbin)
                check_sequence 200 28
	        # Build cross binutils
		export PATH=$PATHORIG
		build_bin $dTRPTARGET $TOOLINSTDIR \
		    "--with-sysroot=$ETOOLSYSROOT --disable-nls --with-libexpat-prefix=$HOSTLIBINST/usr/64 $dBINCONFIG" "prefix=$BUILDINSTDIR" \
		    "all-libiberty" $EBUILDSYSROOT/share/docs
	        ;;
	    Nbin)
                check_sequence 200 28
	        # Build native binutils
		export PATH=$PATHORIG
		build_bin $dTRPTARGET $BUILDINSTDIR \
		    "--build=$dTRPTARGET $dBINCONFIG" "" \
		    "" $BUILDINSTDIR/$dTRPTARGET/share/docs
	        ;;
	    NbinS)
                check_sequence 700 80
	        # Build native binutils
		export PATH=$PATHORIG
		build_bin $dTRPTARGET $BUILDINSTDIR \
		    "--build=$dTRPTARGET --with-sysroot=$INSTLIBDIR $dBINCONFIG" "" \
		    "" $BUILDINSTDIR/$dTRPTARGET/share/docs
		# This is important for tests with DGNAT, and to be included in the tarball
		pushd $INSTLIBDIR/usr/include > /dev/null 2>&1
		cp -rL /usr/include/linux .
		cp -rL /usr/include/asm .
		cp -rL /usr/include/asm-generic .
		popd > /dev/null 2>&1
	        ;;
	    sNbinS)
                check_sequence 700 80
	        # Build native binutils
		export PATH=$PATHORIG
		build_bin $dTRPTARGET $BUILDINSTDIR \
		    "--build=$dTRPTARGET --with-sysroot=$INSTLIBDIR $dBINCONFIG" "" \
		    "LDFLAGS=--static" $BUILDINSTDIR/$dTRPTARGET/share/docs
		# This is important for tests with DGNAT, and to be included in the tarball
		pushd $INSTLIBDIR/usr/include > /dev/null 2>&1
		cp -rL /usr/include/linux .
		cp -rL /usr/include/asm .
		cp -rL /usr/include/asm-generic .
		popd > /dev/null 2>&1
	        ;;
	    Tbin)
                check_sequence 210 30
	        # Run all binutils tests
		test_bin
	        ;;
	    gccM)
                check_sequence 220 35
	        # Build minimum gcc without headers for linux
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		build_cross_gcc_1 $dTRPTARGET $BUILDSYSROOT $BUILDINSTDIR "$dGCCCONFIG1"
	        ;;
	    gccMl)
                check_sequence 220 35
	        # Build minimum gcc without headers for linux
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"

		touch x.c
		${dTBUILD}gcc -c x.c
		x=`file x.o | grep 64-bit`
		rm -f x.c x.o
		if [ "$x" != "" ]; then x="/64"; fi

		LDPATH="$HOSTLIBINST/usr$x/lib"
		build_cross_gcc_1 $dTRPTARGET $BUILDSYSROOT $BUILDINSTDIR "$dGCCCONFIG1 \
		    --with-gmp=$HOSTLIBINST/usr$x \
                    --with-mpfr=$HOSTLIBINST/usr$x \
		    --with-mpc=$HOSTLIBINST/usr$x --with-ppl=$HOSTLIBINST/usr$x \
                    $WITHISL --with-cloog=$HOSTLIBINST/usr$x --enable-cloog-backend=isl"
		LDPATH=""
	        ;;
	    EgccM)
                check_sequence 220 35
	        # Build minimum gcc without headers for eabi
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		build_cross_gcc_eabi_alt $dTRPTARGET "$dGCCCONFIG1"
	        ;;
	    EgccMl)
                check_sequence 220 35
	        # Build minimum gcc without headers for eabi
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"

		touch x.c
		${dTBUILD}gcc -c x.c
		x=`file x.o | grep 64-bit`
		rm -f x.c x.o
		if [ "$x" != "" ]; then x="/64"; fi

		LDPATH="$HOSTLIBINST/usr$x/lib"
		build_cross_gcc_eabi_alt $dTRPTARGET "$dGCCCONFIG3 \
		    --with-gmp=$HOSTLIBINST/usr$x --with-target-gmp=$HOSTLIBINST/tgmp$x --disable-target-multilib \
                    --with-mpfr=$HOSTLIBINST/usr$x \
		    --with-mpc=$HOSTLIBINST/usr$x --with-ppl=$HOSTLIBINST/usr$x \
                    $WITHISL --with-cloog=$HOSTLIBINST/usr$x --enable-cloog-backend=isl"
	        ;;
            sEgdb)
                check_sequence 250 40
	        # Build gdb
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		build_gdb $dTRPTARGET $TOOLINSTDIR \
		    "--with-sysroot=$ETOOLSYSROOT --with-libexpat-prefix=$HOSTLIBINST/usr $dBINCONFIG" "prefix=$BUILDINSTDIR" \
		    "LDFLAGS=--static" $EBUILDSYSROOT/share/docs
	        ;;
	    lhdr)
                check_sequence 230 40
	        # Build linux headers
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		build_linuxhdrs $dARCH $dTRPTARGET $BUILDSYSROOT/usr
	        ;;
	    ghdr)
                check_sequence 240 45
	        # Build glibc headers
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		build_glibchdrs $dTRPTARGET $BUILDSYSROOT "$dLIBCONFIG"
	        ;;
	    rhdr)
                check_sequence 290 46
	        # Build glibc headers
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		build_rpchdrs $BUILDSYSROOT
	        ;;
	    gccS)
                check_sequence 300 55
	        # Build minimum gcc with sysroot
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		build_cross_gcc_2 $dTRPTARGET "$dGCCCONFIG2"
	        ;;
	    gccSl)
                check_sequence 300 55
	        # Build minimum gcc with sysroot
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"

		touch x.c
		${dTBUILD}gcc -c x.c
		x=`file x.o | grep 64-bit`
		rm -f x.c x.o
		if [ "$x" != "" ]; then x="/64"; fi

		LDPATH="$HOSTLIBINST/usr$x/lib"
		build_cross_gcc_2 $dTRPTARGET "$dGCCCONFIG2 \
		    --with-gmp=$HOSTLIBINST/usr$x \
                    --with-mpfr=$HOSTLIBINST/usr$x \
		    --with-mpc=$HOSTLIBINST/usr$x --with-ppl=$HOSTLIBINST/usr$x \
                    $WITHISL --with-cloog=$HOSTLIBINST/usr$x --enable-cloog-backend=isl"
		LDPATH=""
	        ;;
	    linkeabi)
		check_sequence 310 58
		# Create soft links
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		fix_links $dTRPTARGET $BUILDINSTDIR powerpc-elf64-
		;;
	    glibc)
                check_sequence 400 60
	        # Build glibc
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		build_cross_glibc $dTRPTARGET $BUILDSYSROOT "$dLIBCONFIG"
	        ;;
	    rpc)
                check_sequence 480 61
	        # Build glibc
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		build_cross_rpc $dTRPTARGET $BUILDSYSROOT
	        ;;
	    newlib64)
		check_sequence 400 60
		# Build newlib
		FAKETOOLS=gnu-gcc-4.4.0-binutils-2.19-newlib-4.3-75-Xe500mc64-multilib-powerpc64-unknown-linux-gnu/i686-pc-linux2.4
		FAKETARGET=powerpc64-unknown-linux-gnu
		export PATH="$INSTALLDIR/$FAKETOOLS/bin:$PATHORIG"
		CONFIGENV="CC_FOR_TARGET=\"powerpc-elf64-gcc -mcpu=e500mc64\" CC=\"gcc\" AR=\"ar\""
		build_newlib $dTRPTARGET "$dLIBCONFIG"
		CONFIGENV=""
		# Install sysroot on fake tools dir
		#cp -a $INSTALL/$dTRPTARGET/include $INSTALLDIR/$FAKETOOLS/$FAKETARGET
		#cp -a $INSTALL/$dTRPTARGET/lib $INSTALLDIR/$FAKETOOLS/$FAKETARGET
		#tar xjf sys-include.tar.bz2 $INSTALLDIR/$FAKETOOLS/$FAKETARGET
		;;
	    newlib)
		check_sequence 400 60
		# Build newlib
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		build_newlib $dTRPTARGET "$dLIBCONFIG"
		;;
	    newlib_nano)
		#check_sequence 420 62
		# Build newlib
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		
		NEWLIB_ORIG_PATH=${BUILDINSTDIR}/${dINSTPREFIX}/lib
		NEWLIB_NEW_PATH=${BUILDINSTDIR}/${dINSTPREFIX}/newlib
		
		#Move original NewLib into subfolder
		if [ -d ${NEWLIB_ORIG_PATH} ]; then
		    echoV 1 "Move NewLib for Linux to ${NEWLIB_NEW_PATH}"
		    mkdir -p ${NEWLIB_NEW_PATH}
		    mv ${NEWLIB_ORIG_PATH} ${NEWLIB_NEW_PATH}
		fi
		
		build_newlib_nano "$dTRPTARGET" "$dLIBCONFIG --enable-newlib-global-atexit --enable-newlib-reent-small --disable-newlib-fvwrite-in-streamio --disable-newlib-fseek-optimization --disable-newlib-wide-orient --enable-newlib-nano-malloc --disable-newlib-unbuf-stream-opt --enable-lite-exit --enable-newlib-nano-formatted-io --enable-target-optspace"
		
		# lib dir now conatains nanolib
		if [ -d ${NEWLIB_ORIG_PATH} ]; then
		    for i in ` find ${NEWLIB_ORIG_PATH} -name "*.a" ` ;
		      do
			mv $i ` echo $i | sed 's/.a$/_nano.a/g' ` ;
		      done
		fi
		
	        # Integrate nano lib into Newlib
		if [ -d ${NEWLIB_NEW_PATH}/lib ]; then
		    SAVEDIR=$(pwd)
		    cd ${NEWLIB_ORIG_PATH}
		    find . -name '*_nano.a' -type f -exec cp --parents {} ${NEWLIB_NEW_PATH}/lib \;
		    echoV 1 "NewLib Nano integrated in ${NEWLIB_NEW_PATH}/lib"
		    cd ../
		    rm -rf ${NEWLIB_ORIG_PATH}
		    cd ${SAVEDIR}
	        fi
		;;
	    Tnewlib)
		check_sequence 490 61
		# Test newlib
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		test_newlib
		;;
	    Xgcc)
                check_sequence 500 70
	        # Build final gcc for linux
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		build_cross_gcc_final $dTRPTARGET "$dGCCCONFIG3"
	        ;;
	    Xgccl)
                check_sequence 500 70
	        # Build final gcc for linux
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"

		touch x.c
		${dTBUILD}gcc -c x.c
		x=`file x.o | grep 64-bit`
		rm -f x.c x.o
		if [ "$x" != "" ]; then x="/64"; fi

		LDPATH="$HOSTLIBINST/usr$x/lib"
		build_cross_gcc_final $dTRPTARGET "$dGCCCONFIG3 \
		    --with-gmp=$HOSTLIBINST/usr$x \
                    --with-mpfr=$HOSTLIBINST/usr$x \
		    --with-mpc=$HOSTLIBINST/usr$x --with-ppl=$HOSTLIBINST/usr$x \
                    $WITHISL --with-cloog=$HOSTLIBINST/usr$x --enable-cloog-backend=isl"
		LDPATH=""
	        ;;
	    Ngcc)
		check_sequence 500 70
		# Build native gcc
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		build_native_gcc $dTRPTARGET bootstrap "$dGCCCONFIG3"
		;;
	    Ngccl)
		check_sequence 500 70
		# Build native gcc
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"

		touch x.c
		${dTBUILD}gcc -c x.c
		x=`file x.o | grep 64-bit`
		rm -f x.c x.o
		if [ "$x" != "" ]; then x="/64"; fi

		LDPATH="$HOSTLIBINST/usr$x/lib"
		build_native_gcc $dTRPTARGET bootstrap "$dGCCCONFIG3 \
		    --with-gmp=$HOSTLIBINST/usr$x --with-target-gmp=$HOSTLIBINST/tgmp$x --disable-target-multilib \
                    --with-mpfr=$HOSTLIBINST/usr$x \
		    --with-mpc=$HOSTLIBINST/usr$x --with-ppl=$HOSTLIBINST/usr$x \
                    $WITHISL --with-cloog=$HOSTLIBINST/usr$x --enable-cloog-backend=isl"
		LDPATH=""
		;;
	    sNgccl)
		check_sequence 500 70
		# Build native gcc
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"

		touch x.c
		${dTBUILD}gcc -c x.c
		x=`file x.o | grep 64-bit`
		rm -f x.c x.o
		if [ "$x" != "" ]; then x="/64"; fi

		LDPATH="$HOSTLIBINST/usr$x/lib"
		build_native_gcc $dTRPTARGET "BOOT_LDFLAGS=-static bootstrap" "$dGCCCONFIG3 \
		    --with-gmp=$HOSTLIBINST/usr$x --with-target-gmp=$HOSTLIBINST/tgmp$x --disable-target-multilib \
                    --with-mpfr=$HOSTLIBINST/usr$x \
		    --with-mpc=$HOSTLIBINST/usr$x --with-ppl=$HOSTLIBINST/usr$x \
                    $WITHISL --with-cloog=$HOSTLIBINST/usr$x --enable-cloog-backend=isl"
		LDPATH=""
		;;
	    sNgccpl)
		check_sequence 500 70
		# Build native gcc
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"

		touch x.c
		${dTBUILD}gcc -c x.c
		x=`file x.o | grep 64-bit`
		rm -f x.c x.o
		if [ "$x" != "" ]; then x="/64"; fi

		LDPATH="$HOSTLIBINST/usr$x/lib"
		build_native_gcc $dTRPTARGET "bootstrap" "$dGCCCONFIG3 \
                    --with-mpfr=$HOSTLIBINST/usr$x \
		    --with-mpc=$HOSTLIBINST/usr$x --with-ppl=$HOSTLIBINST/usr$x \
                    $WITHISL --with-cloog=$HOSTLIBINST/usr$x --enable-cloog-backend=isl"
		LDPATH=""
		;;
	    NgccB)
		check_sequence 500 70
		# Build native gcc
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		build_native_gcc $dTRPTARGET all "$dGCCCONFIG3 \
		    --enable-languages=c,c++ --disable-bootstrap"
		;;
	    Egcc)
                check_sequence 500 70
	        # Build final gcc for eabi
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		build_cross_gcc_eabi_final $dTRPTARGET "$dGCCCONFIG3"
	        ;;
	    Egccl_nano)
		#check_sequence 500 69
		# Build GCC to get nano version of standard libraries
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		
		touch x.c
		${dTBUILD}gcc -c x.c
		x=`file x.o | grep 64-bit`
		rm -f x.c x.o
		if [ "$x" != "" ]; then x="/64"; fi
		
		LDPATH="$HOSTLIBINST/usr$x/lib"
		build_cross_gcc_eabi_nano $dTRPTARGET "$dGCCCONFIG3 \
		    --with-gmp=$HOSTLIBINST/usr$x --with-target-gmp=$HOSTLIBINST/tgmp$x --disable-target-multilib \
		    --with-mpfr=$HOSTLIBINST/usr$x \
		    --with-mpc=$HOSTLIBINST/usr$x --with-ppl=$HOSTLIBINST/usr$x \
		$WITHISL --with-cloog=$HOSTLIBINST/usr$x --enable-cloog-backend=isl"
		
		# add nano suffix
		LIBDIR=${BUILDINSTDIR}/${dINSTPREFIX}/lib
		if [ -d ${LIBDIR} ]; then
		    for i in ` find ${LIBDIR} -name "*.a" ` ;
		      do
		        mv $i ` echo $i | sed 's/.a$/_nano.a/g' ` ;
		      done
		fi
		
		;;
	    Egccl)
                check_sequence 500 70
	        # Build final gcc for eabi
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"

		touch x.c
		${dTBUILD}gcc -c x.c
		x=`file x.o | grep 64-bit`
		rm -f x.c x.o
		if [ "$x" != "" ]; then x="/64"; fi

		LDPATH="$HOSTLIBINST/usr$x/lib"
		build_cross_gcc_eabi_final $dTRPTARGET "$dGCCCONFIG3 \
		    --with-gmp=$HOSTLIBINST/usr$x --with-target-gmp=$HOSTLIBINST/tgmp$x --disable-target-multilib \
                    --with-mpfr=$HOSTLIBINST/usr$x \
		    --with-mpc=$HOSTLIBINST/usr$x --with-ppl=$HOSTLIBINST/usr$x \
                    $WITHISL --with-cloog=$HOSTLIBINST/usr$x --enable-cloog-backend=isl"
	        ;;
	    EgccF)
                check_sequence 500 70
	        # Build minimum gcc without headers for eabi
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		build_cross_gcc_eabi_alt $dTRPTARGET "$dGCCCONFIG3"
	        ;;
  	    Laeabi)
	        check_sequence 520 71
		build_libaeabi $BUILDINSTDIR
	        ;;
	    Nglibc)
		check_sequence 600 72
		# Build native glibc
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		build_native_glibc $dTRPTARGET $BUILDINSTDIR $INSTLIBDIR "$dLIBCONFIG"
		;;
	    Nrpc)
		check_sequence 630 73
		# Build native rpc
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		build_native_rpc $dTRPTARGET $BUILDINSTDIR $INSTLIBDIR "$dLIBCONFIG"
		;;
	    Xloc)
		check_sequence 650 74
		# Build locale
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		build_cross_locale $dTRPTARGET "install_root=$BUILDSYSROOT"
		;;
	    Nloc)
                check_sequence 650 74
	        # Build locale
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		build_native_locale $dTRPTARGET $BUILDINSTDIR $INSTLIBDIR
	        ;;
	    Gloc)
		check_sequence 699 75
		pushd $BUILDSYSROOT > /dev/null
		install_multilib_locale $BUILDSYSROOT
		finish_glibc_install $BUILDINSTDIR/$dTRPTARGET $BUILDSYSROOT
		popd > /dev/null
		;;
	    spec)
		check_sequence 700 77
		# Fix spec file
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		if [ -d $BUILDSYSROOT ]; then
		    # It is a cross build fix
		    fix_spec $dTRPTARGET $BUILDINSTDIR $BUILDSYSROOT $TOOLSYSROOT $TOOLINSTDIR/$dTRPTARGET
		elif [ -d $EBUILDSYSROOT -a "$dNATIVE" != "Y" ]; then
		    # It is a cross build fix
		    fix_spec $dTRPTARGET $BUILDINSTDIR $EBUILDSYSROOT $TOOLSYSROOT $TOOLINSTDIR/$dTRPTARGET
		else
		    # It is a native build fix
		    fix_spec $dTRPTARGET $BUILDINSTDIR $INSTLIBDIR $INSTLIBDIR
		fi
		;;
	    BMspec)
		check_sequence 710 77
		# Fix spec file for bare metal use
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		fix_bmspec $dTRPTARGET $BUILDINSTDIR $BMSUPDIR
		;;
	    link)
		check_sequence 720 78
		# Create soft links
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		fix_links $dTRPTARGET $BUILDINSTDIR
		;;
	    Tgccbm)
                check_sequence 900 80
	        # Run all gcc tests
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		test_gcc_bm $dTRPTARGET $BUILDINSTDIR
	        ;;
	    Tgcc)
                check_sequence 900 80
	        # Run all gcc tests
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		test_gcc $dTRPTARGET $BUILDINSTDIR
	        ;;
	    Tgcceabi)
                check_sequence 900 80
	        # Run all gcc tests
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		test_gcc_eabi $dTRPTARGET $BUILDINSTDIR
	        ;;
	    Tglibc)
                check_sequence 950 85
	        # Run all glibc tests
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		test_glibc
	        ;;
	    tar)
	        check_sequence 999 99
                # for linux
		strip_host $BUILDINSTDIR "$dTBUILD"
		strip_target $BUILDINSTDIR
		mkdir -p $RELEASEDIR
		x=`uname -r`
		if [ "$x" = "2.6.18-164.11.1.el5" -o "$x" = "2.6.18-308.el5" -o "$x" = "2.6.18-348.el5" -o "$x" = "2.6.18-348.1.1.el5" ]; then
		    cdeprefix="CDE."
		else
		    cdeprefix=""
		fi
		# Find the revision number that the compiler was built from
		if [ "$dNATIVE" = "Y" ]; then
		    revnum=`$BUILDINSTDIR/bin/gcc -v 2>&1 | grep build.sh | awk '{for (i=1; i<=NF; i++) {if (substr($i,1,4)=="rev=") print substr($i,5)}}'`
		else
		    revnum=`$BUILDINSTDIR/bin/$dTRPTARGET-gcc -v 2>&1 | grep build.sh | awk '{for (i=1; i<=NF; i++) {if (substr($i,1,4)=="rev=") print substr($i,5)}}'`
		fi
		rev="r$revnum"
		# Create a release tarball
		echoV 1 "Creating release tarball: ${cdeprefix}$dINSTPREFIX-${PREFIXHOST}-$rev.tar.bz2 $dINSTPREFIX"
		# TR does not like soft links
		pushd $BUILDINSTDIR > /dev/null
		for l in `find . -type l`; do
		    f=`readlink -e $l`
		    rm -f $l; ln $f $l
		done
		popd > /dev/null
		cp -rf patches_applied $BUILDINSTDIR
		if [ "$argINSTSTYLE" = "H" ];then 
		    tar cjf $RELEASEDIR/${cdeprefix}$dINSTPREFIX-${PREFIXHOST}-$rev.tar.bz2 -C $SCRATCH $dINSTPREFIX/$PREFIXHOST
		else
		    tar cjf $RELEASEDIR/${cdeprefix}$dINSTPREFIX-${PREFIXHOST}-$rev.tar.bz2 -C $SCRATCH $dINSTPREFIX
		fi
		;;
	    Wsetup)
	        echoV 1 "Setting up for mingwin canadian build"
	        let LASTSEQ=0
		if [ "$BUILDINSTDIR" != "$WBUILDINSTDIR" ]; then
		    rm -rf $WBUILDINSTDIR x.tar
		    mkdir -p $WBUILDINSTDIR
		    tar cjf x.tar -C $BUILDINSTDIR include lib libexec share $dTRPTARGET
		    tar xjf x.tar -C $WBUILDINSTDIR
		fi
		rm -rf $WBUILDINSTDIR/bin $WBUILDINSTDIR/$dTRPTARGET/bin
		rm -f $WBUILDINSTDIR/libexec/gcc/$dTRPTARGET/*/* > /dev/null 2>&1
		rm -f x.tar
	        ;;
	    Wiconv)
 	        check_sequence 730 15
		# Build libiconv
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		build_canadian_lib_target libiconv \
		    "--disable-shared --disable-nls  RC=${dWTBUILD}windres "
	        ;;
	    Wgtext)
                check_sequence 735 18
	        # Build gmp libraries
		export PATH=$PATHORIG
		build_canadian_lib gettext \
		    "--disable-shared --disable-threads RC=${dWTBUILD}windres --with-libiconv-prefix=$WHOSTLIBINST/usr"
	        ;;
	    Wgmp)
                check_sequence 740 20
	        # Build gmp libraries
		export PATH=$PATHORIG
		build_canadian_lib gmp \
		    "$dWGMPCONFIG --disable-shared --disable-nls"
	        ;;
	    Wmpfr)
                check_sequence 750 22
	        # Build mpfr libraries
		export PATH=$PATHORIG
		build_canadian_lib mpfr \
		    "--disable-shared --disable-nls --with-gmp=$WHOSTLIBINST/usr"
	        ;;
	    Wmpc)
                check_sequence 760 24
	        # Build mpc libraries
		export PATH=$PATHORIG
		build_canadian_lib mpc \
		    "--disable-shared --disable-nls --with-gmp=$WHOSTLIBINST/usr --with-mpfr=$WHOSTLIBINST/usr"
	        ;;
	    Wppl)
                check_sequence 770 26
	        # Build ppl libraries
		export PATH=$PATHORIG
		build_canadian_lib ppl \
		    "--disable-shared --disable-nls $dWPPLCONFIG"
	        ;;
	    Wcloog)
                check_sequence 780 28
	        # Build cloog libraries
		export PATH=$PATHORIG
		if [ -e src_isl ]; then
		    build_canadian_lib isl \
			"--disable-shared --disable-nls --with-gmp=system --with-gmp-prefix=$WHOSTLIBINST/usr"
		    WITHISL="--with-isl=$WHOSTLIBINST/usr"
		else
		    WITHISL=""
		fi
		build_canadian_lib cloog \
		    "--disable-shared --disable-nls $dWCLOOGCONFIG $WITHISL --with-gmp=system --with-gmp-prefix=$WHOSTLIBINST/usr"
	        ;;
	    Wbin)
                check_sequence 790 30
	        # Build cross binutils
		export PATH=$PATHORIG
		build_canadian_bin $dTRPTARGET "$dWBINCONFIG" $WTOOLSYSROOT
	        ;;
	    WEbin)
                check_sequence 790 30
	        # Build cross binutils
		export PATH=$PATHORIG
		build_canadian_bin $dTRPTARGET "$dWBINCONFIG" $WETOOLSYSROOT
	        ;;
            Wgcc)
                check_sequence 800 32
	        # Build cross gcc
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		LDPATH="$WHOSTLIBINST/usr/lib"
		eval cfg=\"$dWGCCCONFIG\"
		build_canadian_gcc $dTRPTARGET "$cfg \
		    --with-gmp=$WHOSTLIBINST/usr \
                    --with-mpfr=$WHOSTLIBINST/usr \
		    --with-mpc=$WHOSTLIBINST/usr --with-ppl=$WHOSTLIBINST/usr \
                    $WITHISL --with-cloog=$WHOSTLIBINST/usr --enable-cloog-backend=isl \
                    --with-libiconv-prefix=$WHOSTLIBINST/usr" \
		    $WBUILDSYSROOT $WTOOLSYSROOT
		LDPATH=""
	        ;;
            WEgcc)
                check_sequence 800 32
	        # Build cross gcc
		export PATH="$BUILDINSTDIR/bin:$PATHORIG"
		LDPATH="$WHOSTLIBINST/usr/lib"
		eval cfg=\"$dWGCCCONFIG\"
		build_canadian_gcc $dTRPTARGET "$cfg \
		    --with-gmp=$WHOSTLIBINST/usr \
                    --with-mpfr=$WHOSTLIBINST/usr \
		    --with-mpc=$WHOSTLIBINST/usr --with-ppl=$WHOSTLIBINST/usr \
                    $WITHISL --with-cloog=$WHOSTLIBINST/usr --enable-cloog-backend=isl \
                    --with-libiconv-prefix=$WHOSTLIBINST/usr" \
		    $WEBUILDSYSROOT $WETOOLSYSROOT
		LDPATH=""
	        ;;
	    Wexpat)
                check_sequence 785 29
	        # Build expat libraries
		export PATH=$PATHORIG
		build_canadian_lib expat "--disable-shared --disable-nls"
	        ;;
            Wgdb)
                check_sequence 860 40
	        # Build gdb
		export PATH=$PATHORIG
		build_canadian_gdb $dTRPTARGET "--with-libexpat-prefix=$WHOSTLIBINST/usr $dWBINCONFIG" $WETOOLSYSROOT
	        ;;
	    Wtar)
	        check_sequence 999 99
                # for windows
	        strip_host $WBUILDINSTDIR "$WTBUILD" ".exe"
		strip_target $WBUILDINSTDIR
		mkdir -p $RELEASEDIR
		x=`uname -r`
		if [ "$x" = "2.6.18-164.11.1.el5" ]; then
		    cdeprefix="CDE."
		else
		    cdeprefix=""
		fi
		# Find the revision number that the compiler was built from
		revnum=`$BUILDINSTDIR/bin/$dTRPTARGET-gcc -v 2>&1 | grep build.sh | awk '{for (i=1; i<=NF; i++) {if (substr($i,1,4)=="rev=") print substr($i,5)}}'`
		rev="r$revnum"
		# Create a release tarball
		echoV 1 "Creating windows release tarball: ${cdeprefix}$dINSTPREFIX-${PREFIXWINHOST}-$rev.tar.bz2 $dINSTPREFIX"
		# Windows does not like soft links
		pushd $WBUILDINSTDIR > /dev/null
		for l in `find . -type l`; do
		    f=`readlink -e $l`
		    rm -f $l; ln $f $l
		done
		popd > /dev/null
		cp -rf patches_applied $WBUILDINSTDIR
		if [ "$argINSTSTYLE" = "H" ];then 
		    tar cjf $RELEASEDIR/${cdeprefix}$dINSTPREFIX-${PREFIXWINHOST}-$rev.tar.bz2 -C $SCRATCH $dINSTPREFIX/$PREFIXWINHOST
		else
		    tar cjf $RELEASEDIR/${cdeprefix}$dINSTPREFIX-${PREFIXWINHOST}-$rev.tar.bz2 -C $SCRATCH $dINSTPREFIX
		fi
		;;
        RelNotes)
                # generate Release notes from texi
                if [ -f $REPODIR/build_gnu/releasenotes.texi ]; then
                  [ -f releasenotes.pdf ] && rm releasenotes.pdf
                  texi2pdf --clean --silent $REPODIR/build_gnu/releasenotes.texi
                  [ -d $BUILDINSTDIR ] && cp releasenotes.pdf $BUILDINSTDIR && echoV 1 "Release Notes for Linux done"
                  [ -d $WBUILDINSTDIR ] && cp releasenotes.pdf $WBUILDINSTDIR && echoV 1 "Release Notes for Windows done"
                fi
                ;;
            *)
	        echoV 0 "[execute_job] Invalid execution step: $s"
	        build_exit 1
		;;
	esac
    done
}

################################################################################
# Host descriptors definitions
################################################################################
#
HIA32=([0]="i686-redhat-linux" [1]="32")
HIA64=([0]="x86_64-redhat-linux" [1]="64")
HPPC32=([0]="powerpc-unknown-linux-gnu" [1]="32")
HPPC64=([0]="powerpc64-unknown-linux-gnu" [1]="mode64")

get_descriptors () {
    # Function to pre-process descriptor array loaded from SRCDESC, JOBDESC and TSTDESC

    # Argument is job descriptor name
    local JD=$1

    local idx=(
	0 1 2
	10 11 12 13 14 15 16 17 18 19
	30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50
	60 61 62 63 64 65 66
	70 71 72 73 74
    )
    local name=(
	"dINSTPREFIX" "dLSTSOURCES" "dLSTPATCHES"
	"dLSTSTEPS" "dTRPTARGET" "dTRPBUILD" "dTRPHOST" "dARCH" "dTBUILD" "dWTBUILD" "dUSESYS" "dNATIVE" "dHOSTTOOLS"
  	"dBINCONFIG" "dGCCCONFIG1" "dGCCCONFIG2" "dGCCCONFIG3" "dLIBCONFIG"
	  "dGMPCONFIG32" "dGMPCONFIG64" "dTGMPCONFIG32" "dTGMPCONFIG64" 
	  "dPPLCONFIG32" "dPPLCONFIG64" "dCLOOGCONFIG32" "dCLOOGCONFIG64"
	  "dWGMPCONFIG" "dWPPLCONFIG" "dWCLOOGCONFIG" "dWBINCONFIG" "dWGCCCONFIG" "dWZLIBCONFIG" "dGCCMAKE"
	  "dLIBBUILD"
	"dMLSIZE" "dMLDIRS" "dMLCONFIG" "dMLCFLAGS" "dMLTARGET" "dMLDEJAGNU" "dMLOSDIRS"
	"dBRDTYPE" "dBRDNAME" "dBRDHOSTNAME" "dBRDLIBDIR" "dBRDRUNTESTFLAGS"
    )
    local op=(
	"c" "j" "j"
	"j" "u" "u" "u" "u" "u" "u" "u" "u" "u"
	"j" "j" "j" "j" "j" "j" "j" "j" "j" "j" "j" "j" "j" "j" "j" "j" "j" "j" "j" "j" "j"
	"u" "m" "m" "m" "m" "m" "m"
	"u" "u" "u" "u" "u"
    )
    local i j cnt idx_i name_i op_i x1 x2 x3 xl1 xl2 xl3 z

    for ((i=0; i < ${#idx[@]}; i++)); do
	idx_i=${idx[$i]}
	name_i=${name[$i]}
	op_i=${op[$i]}
	x1=${SRCDESC[$idx_i]}
	x2=${JOBDESC[$idx_i]}
	x3=${TSTDESC[$idx_i]}
	case $op_i in
	    "c")
		# Concatenate
		eval $name_i=\"${x1}${x2}${x3}\"
		;;
	    "j")
		# Join the lists together
		eval $name_i=\"$x1 $x2 $x3\"
		;;
	    "u")
		# Unique: Only one of them must be non empty
		if [ "$x1" != "" -a "$x2" != "" -o "$x1" != "" -a "$x3" != "" -o "$x2" != "" -a "$x3" != "" ]; then
		    echoV 0 "[get_descriptor] Invalid usage of $name_i (type u)"
		    build_exit 1
		fi
		eval $name_i=\"${x1}${x2}${x3}\"
		;;
	    "m")
		# Each side is a list (or empty). Merge one my one
		eval xl1=($x1)
		eval xl2=($x2)
		eval xl3=($x3)
		[ ${#xl1[@]} -ne 0 ] && cnt=${#xl1[@]}
		[ ${#xl2[@]} -ne 0 ] && cnt=${#xl2[@]}
		[ ${#xl3[@]} -ne 0 ] && cnt=${#xl3[@]}
		z="\\\"${xl1[0]}${xl2[0]}${xl3[0]}\\\""
		for ((j=1; j < $cnt; j++)); do
		    z="$z \\\"${xl1[$j]}${xl2[$j]}${xl3[$j]}\\\""
		done
		eval $name_i=\"$z\"
		;;
	    *)
		echoV 0 "[get_descriptors] Unknown op $op_i, at position $i, index $idx_i"
		build_exit 1
		;;
	esac
    done
    if [ "$cmdLSTSTEPS" != "" ]; then
	dLSTSTEPS=$cmdLSTSTEPS
    fi
    echoV 1 "Execution steps:"
    echoV 1 "   $dLSTSTEPS"
    eval aMLDIRS=("${dMLDIRS[@]}")
    eval aMLOSDIRS=("${dMLOSDIRS[@]}")
    eval aMLCONFIG=("${dMLCONFIG[@]}")
    eval aMLCFLAGS=("${dMLCFLAGS[@]}")
    eval aMLTARGET=("${dMLTARGET[@]}")
    eval aMLDEJAGNU=("${dMLDEJAGNU[@]}")
    echo -n "" > $JD.descriptors 2>&1
    for ((i=0; i < ${#idx[@]}; i++)); do
	name_i=${name[$i]}
	echo "export ${name_i}=\"${!name_i}\"" >> $JD.descriptors 2>&1
    done
}

################################################################################
# Program entry point
################################################################################

# This script provide local customization of this script
scriptdir=`dirname $0`
hnfull=`hostname`
hn=`basename $hnfull .am.freescale.net`
hn=`basename $hn .mtwk.freescale.net`
case $hn in
    lc2*-tx30) hn=lsf_host
esac
source $scriptdir/build.env-$hn
PATHORIG=$PATH

if [ "$BUILD_SVN" = "" ]; then
    BUILD_SVN=http://svn.freescale.net/svn/gcc
fi

LOCALDIR=`pwd`
export DEJAGNU=$REPODIR/build_gnu/global_dejagnu.exp
BUILDINSTDIR=""
TOOLINSTBASE=/opt/freescale

PREFIXHOST=invalid
PREFIXWINHOST=i686-w64-mingw32
CONFIGENV=""
BUILDENV=""
INSTALLENV=""
TDY=`date +%Y%m%d`
DGDESC=""
setPATCHES=""
STP=""
USER=`id -un`
argVERB=1

# Get revision number of this software
BLDscript=`readlink -e $0`
BLDdir=`dirname $BLDscript`
pushd $BLDdir > /dev/null
BLDrevnum=`svn info | grep 'Revision' | awk '{print $2}'`
popd > /dev/null

INVOKED="$@"

declare -a PARAM
parse_args "$@"
SCRATCH=$LOCALDIR/$TOOLINSTBASE
mkdir -p $SCRATCH
cd $SCRATCH

echoV 1 "###========================================================================="
echoV 1 "rev=$BLDrevnum     `date`              Machine: $hn"
echoV 1 "build.sh $INVOKED"
echoV 1 "Installation base directory: $TOOLINSTBASE"

for j in "${PARAM[@]}"; do
    case $j in
	rev=*)
	    # Do the build with the given subversion revision
	    flgREV="Y"
	    BLDrevnum=${j:4}
	    let BLDrevnum=$BLDrevnum
	    if [ $BLDrevnum -le 0 ]; then
		echoV 0 "[job loop] Invalid revision number: $BLDrevnum"
		build_exit 1
	    fi
            echoV 1 "Checking out build revision $BLDrevnum"
	    svn --quiet co -r $BLDrevnum "$BUILD_SVN/build_gnu"
	    cp -f $scriptdir/build.env-$hn build_gnu
	    echo "REPODIR=`pwd`" >> build_gnu/build.env-$hn
	    ln -s $REPODIR/pkg .
	    REFINVOKED=`echo $INVOKED | sed s:rev=[^\ ]*\ ::g`
	    `pwd`/build_gnu/build.sh $REFINVOKED
	    build_exit 0
            ;;
	s=*)
	    # Set a source list to use
	    x=${j:2}
	    SRCFRAG=$x
	    source $REPODIR/build_gnu/f-sources/$x
	    echoV 1 "Switching to sources: $x"
	    ;;
	t=*)
	    # Set a dejagnu descriptor to use
	    DGDESC=${j:2}
	    source $REPODIR/build_gnu/f-targets/$DGDESC
	    echoV 1 "Dejagnu descriptor:   $DGDESC"
	    ;;
	T=*)
	    # Set a individual test to execute
	    TESTFLAGS=${j:2}
	    echoV 1 "Individual tests:     $TESTFLAGS"
	    ;;
	u=*)
	    # Set username to be used in remote connections
	    USER=${j:2}
	    echoV 1 "Username for boards:  $USER"
	    ;;
	p=*)
	    # Add a patch list to use
	    lst=${j:2}
	    setPATCHES="$setPATCHES $lst"
	    echoV 1 "Adding patch:         $lst"
	    ;;
	B=*)
	    # Set the path to find bare metal support files
	    BMSUPDIR=${j:2}
	    echoV 1 "Copying BM support:   $BMSUPDIR"
	    ;;
	*)
	    # Access a bunch of env arrays with job number
	    source $REPODIR/build_gnu/f-jobs/$j
	    get_descriptors $j
	    if [ "$dTRPTARGET" = "" ]; then
		echoV 0 "[job loop] Invalid job descriptor: $j"
		build_exit 1
	    fi
	    if [ "$dHOSTTOOLS" != "" ]; then
		echoV 1 "Using host tools: $dHOSTTOOLS"
		export PATHORIG="$dHOSTTOOLS:$PATHORIG"
		export PATH=$PATHORIG
	    fi
	    # Create job directory
	    mkdir -p $j/logs
	    cd $j
	    # Compose from above
	    LOGFILE=$SCRATCH/$j/logs/build

	    m=`uname -m`
	    touch x.c
	    ${dTBUILD}gcc -c x.c
	    x=`file x.o | grep 64-bit`
	    if [ "$x" != "" ]; then
		x=`uname -m`
		if [ "$x" = "ppc64" -o "$x" = "ppc" ]; then
		    PREFIXHOST=ppc64-linux
		else
		    PREFIXHOST=x86_64-linux
		fi
	    else
		x=`uname -m`
		if [ "$x" = "ppc64" -o "$x" = "ppc" ]; then
		    PREFIXHOST=ppc64-linux
		else
		    PREFIXHOST=i686-linux
		fi
	    fi

	    if [ "$argINSTSTYLE" = "H" ];then 
		BUILDINSTDIR=$SCRATCH/$dINSTPREFIX/$PREFIXHOST
		WBUILDINSTDIR=$SCRATCH/$dINSTPREFIX/$PREFIXWINHOST
		TOOLINSTDIR=$TOOLINSTBASE/$dINSTPREFIX/$PREFIXHOST
		WTOOLINSTDIR=$TOOLINSTBASE/$dINSTPREFIX/$PREFIXWINHOST
	    else
		BUILDINSTDIR=$SCRATCH/$dINSTPREFIX
		WBUILDINSTDIR=$SCRATCH/$dINSTPREFIX
		TOOLINSTDIR=$TOOLINSTBASE/$dINSTPREFIX
		WTOOLINSTDIR=$TOOLINSTBASE/$dINSTPREFIX
	    fi
	    BUILDSYSROOT=$BUILDINSTDIR/$dTRPTARGET/libc
	    WBUILDSYSROOT=$WBUILDINSTDIR/$dTRPTARGET/libc
	    TOOLSYSROOT=$TOOLINSTDIR/$dTRPTARGET/libc
	    WTOOLSYSROOT=$WTOOLINSTDIR/$dTRPTARGET/libc
	    EBUILDSYSROOT=$BUILDINSTDIR/$dTRPTARGET
	    WEBUILDSYSROOT=$WBUILDINSTDIR/$dTRPTARGET
	    ETOOLSYSROOT=$TOOLINSTDIR/$dTRPTARGET
	    WETOOLSYSROOT=$WTOOLINSTDIR/$dTRPTARGET
	    HOSTLIBINST=$SCRATCH/$j/linux_host_libs
	    WHOSTLIBINST=$SCRATCH/$j/mingw32_host_libs
	    INSTLIBDIR=$BUILDINSTDIR/$dTRPTARGET
	    # Process job
	    echoV 0 "#RESET_INFO $SCRATCH/$dINSTPREFIX $SCRATCH/$j $SCRATCH/$j.descriptors"
	    execute_job $j $dLSTSTEPS
	    cd ../
	    ;;
    esac
done
[ "$STP" = "" ] && echoV 0 "#DONE"
build_exit 0
