.DEFAULT: all
.PHONY:
all: binutils-2.24.90.tar.bz2 cloog-0.18.1.tar.gz expat-2.1.0.tar.gz gettext-0.19.4.tar.xz isl-0.12.2.tar.bz2 libelf-0.8.13.tar.gz gmp-6.0.0.tar.bz2 gcc-4.9.2.tar.bz2 mpc-1.0.2.tar.gz mpc-1.0.2.tar.gz mpfr-3.1.2.tar.bz2 newlib-2.2.0.tar.gz zlib-1.2.8.tar.xz newlib-2.2.0.tar.gz libiconv-1.14.tar.gz


gcc-4.9.2.tar.bz2:
	wget -O ${@} https://ftp.gnu.org/gnu/gcc/gcc-4.9.2/${@}

binutils-2.24.90.tar.bz2:
	wget https://www.mirrorservice.org/sites/sourceware.org/pub/binutils/snapshots/$@

cloog-0.18.1.tar.gz:
	wget http://ftp.nluug.nl/languages/gcc/infrastructure/$@

expat-2.1.0.tar.gz:
	wget --output-document=${@} https://sourceforge.net/projects/expat/files/expat/2.1.0/$@/download

gettext-0.19.4.tar.xz:
	wget https://ftp.gnu.org/gnu/gettext/$@

isl-0.12.2.tar.bz2:
	wget http://isl.gforge.inria.fr/$@

libelf-0.8.13.tar.gz:
	wget http://www.mr511.de/software/$@

gmp-6.0.0.tar.bz2:
	wget https://gmplib.org/download/gmp/$@

mpc-1.0.2.tar.gz:
	wget https://ftp.gnu.org/gnu/mpc/$@

mpfr-3.1.2.tar.bz2:
	wget http://www.mpfr.org/mpfr-3.1.2/$@


zlib-1.2.8: zlib-1.2.8.tar.xz
	tar -xJvf ${<}

zlib-1.2.8.tar.xz:
	wget -O ${@} https://sourceforge.net/projects/libpng/files/zlib/1.2.8/zlib-1.2.8.tar.xz/download

newlib-2.2.0.tar.gz:
	wget ftp://sourceware.org/pub/newlib/newlib-2.2.0.tar.gz

libiconv-1.14.tar.gz:
	wget https://ftp.gnu.org/gnu/libiconv/$@
