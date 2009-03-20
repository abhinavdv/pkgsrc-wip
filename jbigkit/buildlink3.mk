# $NetBSD: buildlink3.mk,v 1.4 2009/03/20 19:43:43 jsonn Exp $

BUILDLINK_TREE+=	jbigkit

.if !defined(JBIGKIT_BUILDLINK3_MK)
JBIGKIT_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.jbigkit+=	jbigkit>=1.6
BUILDLINK_PKGSRCDIR.jbigkit?=	../../wip/jbigkit
BUILDLINK_DEPMETHOD.jbigkit?=	build
.endif # JBIGKIT_BUILDLINK3_MK

BUILDLINK_TREE+=	-jbigkit
