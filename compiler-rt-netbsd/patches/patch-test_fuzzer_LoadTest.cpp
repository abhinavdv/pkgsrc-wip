$NetBSD$

--- test/fuzzer/LoadTest.cpp.orig	2017-08-19 18:02:19.285414503 +0000
+++ test/fuzzer/LoadTest.cpp
@@ -0,0 +1,22 @@
+// This file is distributed under the University of Illinois Open Source
+// License. See LICENSE.TXT for details.
+
+// Simple test for a fuzzer: find interesting value of array index.
+#include <assert.h>
+#include <cstddef>
+#include <cstdint>
+#include <cstring>
+#include <iostream>
+
+static volatile int Sink;
+const int kArraySize = 1234567;
+int array[kArraySize];
+
+extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
+  if (Size < 8) return 0;
+  uint64_t a = 0;
+  memcpy(&a, Data, 8);
+  Sink = array[a % (kArraySize + 1)];
+  return 0;
+}
+