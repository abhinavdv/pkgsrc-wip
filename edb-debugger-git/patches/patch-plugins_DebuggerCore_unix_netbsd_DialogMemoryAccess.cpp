$NetBSD$

--- plugins/DebuggerCore/unix/netbsd/DialogMemoryAccess.cpp.orig	2017-02-18 23:34:06.650717163 +0000
+++ plugins/DebuggerCore/unix/netbsd/DialogMemoryAccess.cpp
@@ -0,0 +1,38 @@
+/*
+Copyright (C) 2006 - 2015 Evan Teran
+                          evan.teran@gmail.com
+
+This program is free software: you can redistribute it and/or modify
+it under the terms of the GNU General Public License as published by
+the Free Software Foundation, either version 2 of the License, or
+(at your option) any later version.
+
+This program is distributed in the hope that it will be useful,
+but WITHOUT ANY WARRANTY; without even the implied warranty of
+MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
+GNU General Public License for more details.
+
+You should have received a copy of the GNU General Public License
+along with this program.  If not, see <http://www.gnu.org/licenses/>.
+*/
+
+#include "DialogMemoryAccess.h"
+#include "ui_DialogMemoryAccess.h"
+
+namespace DebuggerCorePlugin {
+
+DialogMemoryAccess::DialogMemoryAccess(QWidget *parent) : QDialog(parent), ui(new Ui::DialogMemoryAccess) {
+	ui->setupUi(this);
+	adjustSize();
+	setFixedSize(width(), height());
+}
+
+DialogMemoryAccess::~DialogMemoryAccess() {
+	delete ui;
+}
+
+bool DialogMemoryAccess::warnNextTime() const {
+	return !ui->checkNeverShowAgain->isChecked();
+}
+
+}
