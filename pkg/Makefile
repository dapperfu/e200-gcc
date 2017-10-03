.DEFAULT: all
.PHONY:
all: binutils-2.24.90.tar.bz2 cloog-0.18.1.tar.gz expat-2.1.0.tar.gz gettext-0.19.4.tar.xz isl-0.12.2.tar.bz2 libelf-0.8.13.tar.gz gmp-6.0.0.tar.bz2



binutils-2.24.90.tar.bz2:
	wget --output-file=$@ https://www.mirrorservice.org/sites/sourceware.org/pub/binutils/snapshots/$@

cloog-0.18.1.tar.gz:
	wget --output-file=$@ http://ftp.nluug.nl/languages/gcc/infrastructure/$@

expat-2.1.0.tar.gz:
	wget --output-file=$@ https://sourceforge.net/projects/expat/files/expat/2.1.0/expat-2.1.0.tar.gz/download

gettext-0.19.4.tar.xz:
	wget --output-file=$@ https://ftp.gnu.org/gnu/gettext/$@

isl-0.12.2.tar.bz2:
	wget --output-file=$@ http://isl.gforge.inria.fr/$@

libelf-0.8.13.tar.gz:
	wget --output-file=$@ http://www.mr511.de/software/$@


gmp-6.0.0.tar.bz2:
	wget --output-file=$@ https://gmplib.org/download/gmp/$@

mpc-1.0.2.tar.gz:
	wget --output-file=$@ https://ftp.gnu.org/gnu/mpc/${@}

mpfr-3.1.2.tar.bz2:
	wget --output-file=$@ http://www.mpfr.org/mpfr-3.1.2/$@

zlib-1.2.8.tar.gz:
	wget --output-file=$@ https://zlib.net/fossils/$@
