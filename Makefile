GNU_MAKE_VERSION=4.1

.PHONY: all clean softcompile patch

all : src/monmakeamoi.a

src/monmakeamoi.a : gnumake/make-${GNU_MAKE_VERSION}-patched/config.h 
	(cd $(dir $@) && make)




#
# ./configure if needed
#
gnumake/make-${GNU_MAKE_VERSION}-patched/config.h : gnumake/make-${GNU_MAKE_VERSION}-patched/Makefile.in
	mkdir -p dist && \
	(cd gnumake/make-${GNU_MAKE_VERSION}-patched && autoreconf && ./configure --prefix=$(realpath $(dir $(lastword $(MAKEFILE_LIST))))/dist --program-transform-name='s/make/monmakeamoi/' )

#
# Download original GNU-Make and apply-patch if needed
#
$(addprefix gnumake/make-${GNU_MAKE_VERSION}-, patched/Makefile.in  original/Makefile.in) : 
	mkdir -p gnumake && \
	rm -rf $(dir $@) gnumake/make-${GNU_MAKE_VERSION} && \
	wget -O gnumake/make-${GNU_MAKE_VERSION}.tar.gz "http://ftp.gnu.org/gnu/make/make-${GNU_MAKE_VERSION}.tar.gz" && \
	tar xf gnumake/make-${GNU_MAKE_VERSION}.tar.gz -C gnumake  && \
	mv gnumake/make-${GNU_MAKE_VERSION} $(dir $@) && \
	rm gnumake/make-${GNU_MAKE_VERSION}.tar.gz && \
	touch --no-create $(addprefix $(dir $@), configure.ac aclocal.m4 configure Makefile.am Makefile.in configure )  \
	$(if $(findstring patched,$@),&& (cd $(dir $@) && patch -p2 --backup --input=$(realpath src/${GNU_MAKE_VERSION}.patch ) --batch ) )


#
# Create patch
#
patch : src/${GNU_MAKE_VERSION}.patch.tmp
src/${GNU_MAKE_VERSION}.patch.tmp : $(addprefix gnumake/make-${GNU_MAKE_VERSION}-, patched/configure  original/configure)
	-mkdir -p $(dir $@) && \
	rm -f $@ \
	$(foreach F,function.c Makefile.am, && diff -C5  $(addprefix gnumake/make-${GNU_MAKE_VERSION}-, original/${F} patched/${F} ) >> $@ ) 
	@echo "You can now copy $@ to $(basename $@)"

clean:
	rm -rf gnumake dist
