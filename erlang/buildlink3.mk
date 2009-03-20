# $NetBSD: buildlink3.mk,v 1.2 2009/03/20 19:43:41 jsonn Exp $

BUILDLINK_TREE+=	erlang

.if !defined(ERLANG_BUILDLINK3_MK)
ERLANG_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.erlang+=	erlang>=10.1
BUILDLINK_ABI_DEPENDS.erlang?=	erlang>=10.1.9nb1
BUILDLINK_PKGSRCDIR.erlang?=	../../lang/erlang
.endif # ERLANG_BUILDLINK3_MK

BUILDLINK_TREE+=	-erlang
