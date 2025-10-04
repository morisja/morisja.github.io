# debian packaging

is often confusing, I sometimes need to patch upstream content and have wrestled with pristine-tar, pbuilder etc. Here are my notes

## Overview
When you build debian packages, there are often build-depends, which need to be installed before you can build the package.

Installing these on your host system can get complex, not to mention you may have customized you host system, which can lead to a less than clean build experience.

We'll be using cowbuilder, and making build chroots instead. This means you pre-create miniature reference "cleanrooms" in `/var/cache/pbuilder'; builds make a transient copy of these directories, before installing build depdendencies temporarily. 

## Setup

As root, prep your build chroots, once for each dist you need
```
# DIST=bookworm git-pbuilder create --mirror  http://atl.mirrors.clouvider.net/debian/
```

This will create:
```
/var/cache/pbuilder/base-bookworm.cow
```

Additionally, add a sudo rule to permit cowbuilder to do its thing
```
# cat /etc/sudoers.d/cowbuilder
%sudo ALL=(ALL) NOPASSWD:SETENV: /usr/sbin/cowbuilder
```

## Build
We'll be building jq.. 

Clone using the gbp command, this is important as it configures pristine-tar branches which can sometimes be a pain..  then build

```

jamesm@x1:~/src$ gbp clone --pristine-tar https://salsa.debian.org/debian/jq  && cd jq
jamesm@x1:~/src$ gbp buildpackage --git-verbose --git-ignore-branch --git-pbuilder --git-dist=bookworm

```

Debs will be in the parent dir.

## Patch
Reset the clone
```
jamesm@x1:~/src/jq$ git checkout -- . && git clean -fd
jamesm@x1:~/src/jq$ git status
On branch debian/unstable
Your branch is up to date with 'origin/debian/unstable'.

nothing to commit, working tree clean

```

Edit
```
export QUILT_PATCHES=debian/patches
quilt new demo.patch
quilt edit src/util.h
quilt diff
quilt refresh
git add debian/patches/
git commit -m 'demo patch'
git checkout -- . && git clean -fd
```
This is what my patch looked like:
```
jamesm@x1:~/src/jq$ cat debian/patches/demo.patch 
Index: jq/src/util.h
===================================================================
--- jq.orig/src/util.h
+++ jq/src/util.h
@@ -16,7 +16,7 @@
 jv expand_path(jv);
 jv get_home(void);
 jv jq_realpath(jv);
-
+/* this is a patch */
 /*
  * The Windows CRT and console are something else.  In order for the
  * console to get UTF-8 written to it correctly we have to bypass stdio

```

Repeat the steps above to build - to increment the version number:
```
$ dch -t 'my patch'
$ dch -r ''

jamesm@x1:~/src/jq$ git diff
diff --git a/debian/changelog b/debian/changelog
index 06a8b09..1b5a80c 100644
--- a/debian/changelog
+++ b/debian/changelog
@@ -1,3 +1,9 @@
+jq (1.7.1-3+p1) jammy; urgency=medium
+
+  * my patch
+
+ -- James morris <jamesm@x1>  Mon, 17 Feb 2025 12:36:47 -0500
+
 jq (1.7.1-3) unstable; urgency=medium
 
   [ Helmut Grohne ]
jamesm@x1:~/src/jq$ git add debian/
jamesm@x1:~/src/jq$ git commit -m release

```

More details on cowbuilder

https://wiki.debian.org/cowbuilder
