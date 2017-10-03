.DEFAULT: all
.PHONY:
all: binutils-2.24.90.tar.bz2 cloog-0.18.1.tar.gz expat-2.1.0.tar.gz gettext-0.19.4.tar.xz isl-0.12.2.tar.bz2 libelf-0.8.13.tar.gz gmp-6.0.0.tar.bz2



binutils-2.24.90.tar.bz2:
	wget https://www.mirrorservice.org/sites/sourceware.org/pub/binutils/snapshots/binutils-2.24.90.tar.bz2

cloog-0.18.1.tar.gz:
	wget http://ftp.nluug.nl/languages/gcc/infrastructure/cloog-0.18.1.tar.gz

expat-2.1.0.tar.gz:
	wget --output-file=$@ https://sourceforge.net/projects/expat/files/expat/2.1.0/expat-2.1.0.tar.gz/download


gettext-0.19.4.tar.xz:
	wget --output-file=$@ https://ftp.gnu.org/gnu/gettext/gettext-0.19.4.tar.xz

isl-0.12.2.tar.bz2:
	wget http://isl.gforge.inria.fr/isl-0.12.2.tar.bz2

libelf-0.8.13.tar.gz:
	wget http://www.mr511.de/software/libelf-0.8.13.tar.gz


gmp-6.0.0.tar.bz2:
	wget https://gmplib.org/download/gmp/gmp-6.0.0.tar.bz2

mpc-1.0.2.tar.gz:
	wget https://ftp.gnu.org/gnu/mpc/${@}

mpfr-3.1.2.tar.bz2:
	wget http://www.mpfr.org/mpfr-3.1.2/mpfr-3.1.2.tar.bz2

zlib-1.2.8.tar.gz:
	wget https://zlib.net/fossils/zlib-1.2.8.tar.gz
