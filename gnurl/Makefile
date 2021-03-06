# $NetBSD$

DISTNAME=	gnurl-7.63.0
CATEGORIES=	www
MASTER_SITES=	${MASTER_SITE_GNU:=gnunet/}
EXTRACT_SUFX=	.tar.Z

MAINTAINER=	ng0@n0.is
HOMEPAGE=	https://gnunet.org/gnurl
COMMENT=	Client that groks URLs (micro fork of curl)
# not completely, the curl license is inspired by mit
LICENSE=	mit

# list it into IPv6-ready packages
BUILD_DEFS+=	IPV6_READY

USE_TOOLS+=		nroff perl pkg-config
USE_LIBTOOL=		yes
GNU_CONFIGURE=		yes # make install depends on it
PKGCONFIG_OVERRIDE=	libgnurl.pc.in
INSTALLATION_DIRS=	share/doc/gnurl

.include "../../mk/bsd.prefs.mk"

TEST_TARGET=		check

CONFIGURE_ARGS+=	--disable-ntml-wb
CONFIGURE_ARGS+=	--with-gnutls
CONFIGURE_ARGS+=	--with-libidn2
CONFIGURE_ARGS+=	--with-libz=${BUILDLINK_PREFIX.zlib}
# Fallback to gnutls preferred CA certificates
CONFIGURE_ARGS+=	--without-ca-bundle
CONFIGURE_ARGS+=	--without-ca-path
CONFIGURE_ARGS+=	--with-ca-fallback
# Do not pick up GSS, should be fixed in upstream.
CONFIGURE_ARGS+=	--without-gssapi

.include "options.mk"

post-install:
.for f in MANUAL TheArtOfHttpScripting FAQ
	${INSTALL_DATA} ${WRKSRC}/docs/${f} ${DESTDIR}${PREFIX}/share/doc/gnurl/
.endfor

.include "../../devel/gettext-lib/buildlink3.mk"
.include "../../devel/libidn2/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../security/gnutls/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
