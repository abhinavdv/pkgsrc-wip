.if ${OPSYS} == "Linux"

--- ./src/util/virnetdev.c.orig	2018-09-26 13:26:50.985409786 +0200
+++ ./src/util/virnetdev.c	2018-12-02 21:23:12.483507591 +0100
@@ -3085,217 +3085,6 @@ virNetDevGetEthtoolFeatures(virBitmapPtr
 # endif
 }
 
-
-# if HAVE_DECL_DEVLINK_CMD_ESWITCH_GET
-
-/**
- * virNetDevGetFamilyId:
- * This function supplies the devlink family id
- *
- * @family_name: the name of the family to query
- *
- * Returns family id or 0 on failure.
- */
-static uint32_t
-virNetDevGetFamilyId(const char *family_name)
-{
-    struct nl_msg *nl_msg = NULL;
-    struct nlmsghdr *resp = NULL;
-    struct genlmsghdr gmsgh = {
-        .cmd = CTRL_CMD_GETFAMILY,
-        .version = DEVLINK_GENL_VERSION,
-        .reserved = 0,
-    };
-    struct nlattr *tb[CTRL_ATTR_MAX + 1] = {NULL, };
-    unsigned int recvbuflen;
-    uint32_t family_id = 0;
-
-    if (!(nl_msg = nlmsg_alloc_simple(GENL_ID_CTRL,
-                                      NLM_F_REQUEST | NLM_F_ACK))) {
-        virReportOOMError();
-        goto cleanup;
-    }
-
-    if (nlmsg_append(nl_msg, &gmsgh, sizeof(gmsgh), NLMSG_ALIGNTO) < 0)
-        goto cleanup;
-
-    if (nla_put_string(nl_msg, CTRL_ATTR_FAMILY_NAME, family_name) < 0) {
-        virReportError(VIR_ERR_INTERNAL_ERROR, "%s",
-                       _("allocated netlink buffer is too small"));
-        goto cleanup;
-    }
-
-    if (virNetlinkCommand(nl_msg, &resp, &recvbuflen, 0, 0, NETLINK_GENERIC, 0) < 0)
-        goto cleanup;
-
-    if (nlmsg_parse(resp, sizeof(struct nlmsghdr), tb, CTRL_ATTR_MAX, NULL) < 0) {
-        virReportError(VIR_ERR_INTERNAL_ERROR, "%s",
-                       _("malformed netlink response message"));
-        goto cleanup;
-    }
-
-    if (tb[CTRL_ATTR_FAMILY_ID] == NULL)
-        goto cleanup;
-
-    family_id = *(uint32_t *)RTA_DATA(tb[CTRL_ATTR_FAMILY_ID]);
-
- cleanup:
-    nlmsg_free(nl_msg);
-    VIR_FREE(resp);
-    return family_id;
-}
-
-
-/**
- * virNetDevSwitchdevFeature
- * This function checks for the availability of Switchdev feature
- * and add it to bitmap
- *
- * @ifname: name of the interface
- * @out: add Switchdev feature if exist to bitmap
- *
- * Returns 0 on success, -1 on failure.
- */
-static int
-virNetDevSwitchdevFeature(const char *ifname,
-                          virBitmapPtr *out)
-{
-    struct nl_msg *nl_msg = NULL;
-    struct nlmsghdr *resp = NULL;
-    unsigned int recvbuflen;
-    struct nlattr *tb[DEVLINK_ATTR_MAX + 1] = {NULL, };
-    virPCIDevicePtr pci_device_ptr = NULL;
-    struct genlmsghdr gmsgh = {
-        .cmd = DEVLINK_CMD_ESWITCH_GET,
-        .version = DEVLINK_GENL_VERSION,
-        .reserved = 0,
-    };
-    const char *pci_name;
-    char *pfname = NULL;
-    int is_vf = -1;
-    int ret = -1;
-    uint32_t family_id;
-
-    if ((family_id = virNetDevGetFamilyId(DEVLINK_GENL_NAME)) <= 0)
-        return ret;
-
-    if ((is_vf = virNetDevIsVirtualFunction(ifname)) < 0)
-        return ret;
-
-    if (is_vf == 1 && virNetDevGetPhysicalFunction(ifname, &pfname) < 0)
-        goto cleanup;
-
-    pci_device_ptr = pfname ? virNetDevGetPCIDevice(pfname) :
-                              virNetDevGetPCIDevice(ifname);
-    /* No PCI device, then no feature bit to check/add */
-    if (pci_device_ptr == NULL) {
-        ret = 0;
-        goto cleanup;
-    }
-
-    if (!(nl_msg = nlmsg_alloc_simple(family_id,
-                                      NLM_F_REQUEST | NLM_F_ACK))) {
-        virReportOOMError();
-        goto cleanup;
-    }
-
-    if (nlmsg_append(nl_msg, &gmsgh, sizeof(gmsgh), NLMSG_ALIGNTO) < 0)
-        goto cleanup;
-
-    pci_name = virPCIDeviceGetName(pci_device_ptr);
-
-    if (nla_put(nl_msg, DEVLINK_ATTR_BUS_NAME, strlen("pci")+1, "pci") < 0 ||
-        nla_put(nl_msg, DEVLINK_ATTR_DEV_NAME, strlen(pci_name)+1, pci_name) < 0) {
-        virReportError(VIR_ERR_INTERNAL_ERROR, "%s",
-                       _("allocated netlink buffer is too small"));
-        goto cleanup;
-    }
-
-    if (virNetlinkCommand(nl_msg, &resp, &recvbuflen, 0, 0, NETLINK_GENERIC, 0) < 0)
-        goto cleanup;
-
-    if (nlmsg_parse(resp, sizeof(struct genlmsghdr), tb, DEVLINK_ATTR_MAX, NULL) < 0) {
-        virReportError(VIR_ERR_INTERNAL_ERROR, "%s",
-                       _("malformed netlink response message"));
-        goto cleanup;
-    }
-
-    if (tb[DEVLINK_ATTR_ESWITCH_MODE] &&
-        *(int *)RTA_DATA(tb[DEVLINK_ATTR_ESWITCH_MODE]) == DEVLINK_ESWITCH_MODE_SWITCHDEV) {
-        ignore_value(virBitmapSetBit(*out, VIR_NET_DEV_FEAT_SWITCHDEV));
-    }
-
-    ret = 0;
-
- cleanup:
-    nlmsg_free(nl_msg);
-    virPCIDeviceFree(pci_device_ptr);
-    VIR_FREE(resp);
-    VIR_FREE(pfname);
-    return ret;
-}
-# else
-static int
-virNetDevSwitchdevFeature(const char *ifname ATTRIBUTE_UNUSED,
-                          virBitmapPtr *out ATTRIBUTE_UNUSED)
-{
-    return 0;
-}
-# endif
-
-
-# if HAVE_DECL_ETHTOOL_GFEATURES
-/**
- * virNetDevGFeatureAvailable
- * This function checks for the availability of a network device gfeature
- *
- * @fd: socket to operate on
- * @ifr: struct ifreq with the command
- * @cmd: reference to an ethtool command structure
- *
- * Returns true if the feature is available, false otherwise.
- */
-static bool
-virNetDevGFeatureAvailable(int fd,
-                           struct ifreq *ifr,
-                           struct ethtool_gfeatures *cmd)
-{
-    ifr->ifr_data = (void*)cmd;
-    if (virNetDevSendEthtoolIoctl(fd, ifr) == 0)
-        return !!FEATURE_BIT_IS_SET(cmd->features, TX_UDP_TNL, active);
-    return false;
-}
-
-
-static int
-virNetDevGetEthtoolGFeatures(virBitmapPtr bitmap,
-                             int fd,
-                             struct ifreq *ifr)
-{
-    struct ethtool_gfeatures *g_cmd;
-
-    if (VIR_ALLOC_VAR(g_cmd,
-                      struct ethtool_get_features_block, GFEATURES_SIZE) < 0)
-        return -1;
-
-    g_cmd->cmd = ETHTOOL_GFEATURES;
-    g_cmd->size = GFEATURES_SIZE;
-    if (virNetDevGFeatureAvailable(fd, ifr, g_cmd))
-        ignore_value(virBitmapSetBit(bitmap, VIR_NET_DEV_FEAT_TXUDPTNL));
-    VIR_FREE(g_cmd);
-    return 0;
-}
-# else
-static int
-virNetDevGetEthtoolGFeatures(virBitmapPtr bitmap ATTRIBUTE_UNUSED,
-                             int fd ATTRIBUTE_UNUSED,
-                             struct ifreq *ifr ATTRIBUTE_UNUSED)
-{
-    return 0;
-}
-# endif
-
-
 # if HAVE_DECL_ETHTOOL_SCOALESCE && HAVE_DECL_ETHTOOL_GCOALESCE
 /**
  * virNetDevSetCoalesce:
@@ -3433,15 +3222,9 @@ virNetDevGetFeatures(const char *ifname,
 
     virNetDevGetEthtoolFeatures(*out, fd, &ifr);
 
-    if (virNetDevGetEthtoolGFeatures(*out, fd, &ifr) < 0)
-        return -1;
-
     if (virNetDevRDMAFeature(ifname, out) < 0)
         return -1;
 
-    if (virNetDevSwitchdevFeature(ifname, out) < 0)
-        return -1;
-
     return 0;
 }
 #else

.endif
