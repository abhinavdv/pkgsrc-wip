# $NetBSD: buildlink3.mk,v 1.1.1.1 2007/04/17 05:32:16 marttikuparinen Exp $

BUILDLINK_DEPTH:=			${BUILDLINK_DEPTH}+
XFCE4_EYES_PLUGIN_BUILDLINK3_MK:=	${XFCE4_EYES_PLUGIN_BUILDLINK3_MK}+

.if ${BUILDLINK_DEPTH} == "+"
BUILDLINK_DEPENDS+=	xfce4-eyes-plugin
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nxfce4-eyes-plugin}
BUILDLINK_PACKAGES+=	xfce4-eyes-plugin
BUILDLINK_ORDER:=	${BUILDLINK_ORDER} ${BUILDLINK_DEPTH}xfce4-eyes-plugin

.if ${XFCE4_EYES_PLUGIN_BUILDLINK3_MK} == "+"
BUILDLINK_API_DEPENDS.xfce4-eyes-plugin+=	xfce4-eyes-plugin>=4.4.0
BUILDLINK_PKGSRCDIR.xfce4-eyes-plugin?=	../../wip/xfce4-eyes-plugin
.endif	# XFCE4_EYES_PLUGIN_BUILDLINK3_MK

.include "../../x11/xfce4-panel/buildlink3.mk"
.include "../../devel/xfce4-dev-tools/buildlink3.mk"
.include "../../x11/libSM/buildlink3.mk"
.include "../../x11/gtk2/buildlink3.mk"
.include "../../devel/glib2/buildlink3.mk"

BUILDLINK_DEPTH:=			${BUILDLINK_DEPTH:S/+$//}
