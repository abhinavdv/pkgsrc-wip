# $NetBSD: options.mk,v 1.1.1.1 2011/01/09 05:47:13 makoto Exp $

# Global and legacy options

PKG_OPTIONS_VAR=	PKG_OPTIONS.ffmpeg
PKG_SUPPORTED_OPTIONS=	theora xvid faad faac x264 opencore-amr
PKG_SUGGESTED_OPTIONS=	theora xvid x264
#PKG_OPTIONS_OPTIONAL_GROUPS=	aac-decoder
#PKG_OPTIONS_GROUP.aac-decoder=	faad faac

### Add vdpau if it is available
.include "../../multimedia/libvdpau/available.mk"
.if ${VDPAU_AVAILABLE} == "yes"
PKG_SUPPORTED_OPTIONS+= vdpau
PKG_SUGGESTED_OPTIONS+=	vdpau
.endif

.include "../../mk/bsd.options.mk"

###
### faad option
###

.if !empty(PKG_OPTIONS:Mfaad)
CONFIGURE_ARGS+=  --enable-libfaad
.include "../../audio/faad2/buildlink3.mk"
.endif

###
### faac option
###

.if !empty(PKG_OPTIONS:Mfaac)
RESTRICTED=		This software may require the payment of patent royalties
NO_BIN_ON_CDROM=	${RESTRICTED}
NO_BIN_ON_FTP=		${RESTRICTED}
CONFIGURE_ARGS+=	--enable-libfaac \
			--enable-nonfree
.include "../../audio/faac/buildlink3.mk"
.endif

###
### opencore-amr option
###

.if !empty(PKG_OPTIONS:Mopencore-amr)
CONFIGURE_ARGS+=  --enable-libopencore-amrnb --enable-libopencore-amrwb

# "The OpenCORE external libraries are under the Apache License
# 2.0. That license is incompatible with the LGPL v2.1 and the GPL
# v2, but not with version 3 of those licenses. So to combine the
# OpenCORE libraries with FFmpeg, the license version needs to be
# upgraded by passing --enable-version3 to configure."
CONFIGURE_ARGS+=	--enable-version3
# TODO: LICENSE

.include "../../audio/opencore-amr/buildlink3.mk"
.else
CONFIGURE_ARGS+=  --disable-libopencore-amrnb --disable-libopencore-amrwb
.endif

###
### OGG Theora support
###

.if !empty(PKG_OPTIONS:Mtheora)
CONFIGURE_ARGS+=  --enable-libtheora
.include "../../multimedia/libtheora/buildlink3.mk"
.endif

###
### XviD support
###

.if !empty(PKG_OPTIONS:Mxvid)
CONFIGURE_ARGS+=  --enable-libxvid
.include "../../multimedia/xvidcore/buildlink3.mk"
.endif

###
### x264 support
###

.if !empty(PKG_OPTIONS:Mx264)
# ABI change between 20090326 and 20100201
BUILDLINK_API_DEPENDS.x264-devel+=	x264-devel>=20100201
# incompatible API change on 20090921
BUILDLINK_API_DEPENDS.x264-devel+=	x264-devel<20100202
CONFIGURE_ARGS+=  --enable-libx264
.include "../../wip/x264-devel/buildlink3.mk"
.endif

###
### VDPAU support
###
.if !empty(PKG_OPTIONS:Mvdpau)
.include "../../multimedia/libvdpau/buildlink3.mk"
.else
CONFIGURE_ARGS+=        --disable-vdpau
.endif
