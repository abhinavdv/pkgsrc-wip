# $NetBSD$
#
###########################################################
#                  Generated by fbsd2pkg                  #
#              Mon Nov  5 14:38:46 CST 2018               #
###########################################################

###########################################################
# Unconverted and partially converted FreeBSD port syntax:

#pre-configure: # unbreak for python3: README.rst can't be decoded with the ascii codec: https://github.com/biopython/biopython/issues/1649
#	@truncate -s 0 ${WRKSRC}/README.rst

DISTNAME=	biopython-${PV}
PKGNAME=	${PYPKGPREFIX}-biopython-${PV}
CATEGORIES=	biology
MASTER_SITES=	http://www.biopython.org/DIST/

MAINTAINER=	bacon@NetBSD.org
HOMEPAGE=	http://biopython.org/
COMMENT=	Collection of Python modules for bioinformatics
LICENSE=	modified-bsd

# Many dependencies.  Option?
# DEPENDS+=	${PYPKGPREFIX}-reportlab>0:../../print/py-reportlab
DEPENDS+=	${PYPKGPREFIX}-numpy>0:../../math/py-numpy

PV=		1.72

.include "../../lang/python/egg.mk"
.include "../../mk/bsd.pkg.mk"
