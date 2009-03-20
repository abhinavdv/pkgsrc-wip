# $NetBSD: buildlink3.mk,v 1.4 2009/03/20 19:43:52 jsonn Exp $

BUILDLINK_TREE+=	synfig

.if !defined(SYNFIG_BUILDLINK3_MK)
SYNFIG_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.synfig+=	synfig>=0.61.08
BUILDLINK_PKGSRCDIR.synfig?=	../../wip/synfig

pkgbase:= synfig
.  include "../../mk/pkg-build-options.mk"

.  if !empty(PKG_BUILD_OPTIONS.synfig:Mpng)
.    include "../../graphics/png/buildlink3.mk"
.  endif

.  if !empty(PKG_BUILD_OPTIONS.synfig:Mmng)
.    include "../../graphics/mng/buildlink3.mk"
.  endif

.  if !empty(PKG_BUILD_OPTIONS.synfig:Mjpeg)
.    include "../../graphics/jpeg/buildlink3.mk"
.  endif

.  if !empty(PKG_BUILD_OPTIONS.synfig:Mfreetype)
.    include "../../graphics/freetype2/buildlink3.mk"
.  endif

.  if !empty(PKG_BUILD_OPTIONS.synfig:Mfontconfig)
.    include "../../fonts/fontconfig/buildlink3.mk"
.  endif

.  if !empty(PKG_BUILD_OPTIONS.synfig:Mopenexr)
.    include "../../graphics/openexr/buildlink3.mk"
.  endif

.  if !empty(PKG_BUILD_OPTIONS.synfig:Mlavcodec)
.    include "../../multimedia/ffmpeg/buildlink3.mk"
.  endif

.include "../../devel/gettext-lib/buildlink3.mk"
.include "../../devel/libsigc++/buildlink3.mk"
.include "../../textproc/libxml++/buildlink3.mk"
.include "../../wip/ETL/buildlink3.mk"
.endif # SYNFIG_BUILDLINK3_MK

BUILDLINK_TREE+=	-synfig
