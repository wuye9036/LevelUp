#!/usr/bin/env python
# -*- coding: cp936 -*-

class OpenMode:
	Invalid = "invalid"
	ReadOnly = "r"
	WriteOnly = "w"
	ReadWrite = "rw"
	
	@staticmethod
	def EnumList():
		return [
			OpenMode.Invalid,
			OpenMode.ReadOnly,
			OpenMode.WriteOnly,
			OpenMode.ReadWrite
			]