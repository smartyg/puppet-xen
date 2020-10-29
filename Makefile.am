## Place generated object files (.o) into the same directory as their source
## files, in order to avoid collisions when non-recursive make is used.
AUTOMAKE_OPTIONS = subdir-objects

## Additional flags to pass to aclocal when it is invoked automatically at
## make time. The ${ACLOCAL_FLAGS} variable is picked up from the environment
## to provide a way for the user to supply additional arguments.
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4
# only enable this to test the compiled binary in a local environment, dont install builds when this is enabled
# pkglibdir = /home/martijn/eclipse/workspace/backupprog-c/.libs/

SUBDIRS = src/xen-facter
SUBDIRS += src/libxl-ruby