# -*- coding: cp936 -*-
import os
import filecmp
import stat
import warnings
from itertools import ifilter, ifilterfalse, imap, izip
from filecmp import dircmp, _filter,cmpfiles

class dirBackupList (dircmp):
    def __init__(self, a, b, ignore=None, hide=None): # Initialize
        self.left = a
        self.right = b
        if hide is None:
            self.hide = [os.curdir, os.pardir] # Names never to be shown
        else:
            self.hide = hide
        if ignore is None:
            self.ignore = ['RCS', 'CVS', 'tags'] # Names ignored in comparison
        else:
            self.ignore = ignore
        self.phase0()
        self.phase1()
        self.phase2()
        self.phase3()
        self.subdirs = {}
        self.common_dirs_add = self.common_dirs
        self.phase4_closure_add()
        
    def add_right_dir(self, r):
        self.common_dirs_add = []
        self.common_files_add = []
        self.common_funny_add = []
        
        #保存右dir
        self.right = r
        org_rl = self.right_list
        
        self.right_list = _filter(os.listdir(self.right), self.hide+self.ignore)
        self.right_list.sort()

        #更新left only和right only
        a = dict(izip(imap(os.path.normcase, self.left_list), self.left_list))
        b = dict(izip(imap(os.path.normcase, self.right_list), self.right_list))
        self.common_add = map(a.__getitem__, ifilter(b.has_key, a))
        print self.common_add
        self.common += self.common_add
        left_only_dict  = dict(izip(imap(os.path.normcase, self.left_only), self.left_only))
        self.left_only = map(left_only_dict.__getitem__, ifilterfalse(b.has_key, left_only_dict))
        self.right_only += map(b.__getitem__, ifilterfalse(a.has_key, b))
                
        for x in self.common_add:
            a_path = os.path.join(self.left, x)
            b_path = os.path.join(self.right, x)

            ok = 1
            try:
                a_stat = os.stat(a_path)
            except os.error, why:
                # print 'Can\'t stat', a_path, ':', why[1]
                ok = 0
            try:
                b_stat = os.stat(b_path)
            except os.error, why:
                # print 'Can\'t stat', b_path, ':', why[1]
                ok = 0

            if ok:
                a_type = stat.S_IFMT(a_stat.st_mode)
                b_type = stat.S_IFMT(b_stat.st_mode)
                if a_type != b_type:
                    self.common_funny_add.append(x)
                elif stat.S_ISDIR(a_type):
                    self.common_dirs_add.append(x)
                elif stat.S_ISREG(a_type):
                    self.common_files_add.append(x)
                else:
                    self.common_funny_add.append(x)
            else:
                self.common_funny_add.append(x)

        xx = cmpfiles(self.left, self.right, self.common_files_add)
        self.same_files_add, self.diff_files_add, self.funny_files_add = xx

        self.common_funny += self.common_funny_add
        self.common_dirs += self.common_dirs_add
        self.common_files += self.common_files_add
        self.same_files += self.same_files_add
        self.diff_files += self.diff_files_add
        self.funny_files += self.funny_files_add
        self.right_list += org_rl

        self.phase4_closure_add()
            
    def  phase4_add(self) :     
        for x in self.common_dirs_add:
            a_x = os.path.join(self.left, x)
            b_x = os.path.join(self.right, x)
            if(self.subdirs.has_key(x)):
                self.subdirs[x].add_right_dir(b_x)
            else:
                self.subdirs[x]  = dirBackupList(a_x, b_x, self.ignore, self.hide)          

    def phase4_closure_add(self):
            self.phase4_add()
            for sd in self.subdirs.itervalues():
                sd.phase4_closure_add()

    def __getattr__(self, attr):
        if attr not in self.__dict__:
            raise AttributeError, attr
        return getattr(self, attr)

    def report(self):
        # Output format is purposely lousy
        print 'diff', self.left, self.right
        if self.left_only:
            self.left_only.sort()
            print 'Only in', self.left, ':', self.left_only
        if self.right_only:
            self.right_only.sort()
            print 'Only in', self.right, ':', self.right_only
        if self.same_files:
            self.same_files.sort()
            print 'Identical files :', self.same_files
        if self.diff_files:
            self.diff_files.sort()
            print 'Differing files :', self.diff_files
        if self.funny_files:
            self.funny_files.sort()
            print 'Trouble with common files :', self.funny_files
        if self.common_dirs:
            self.common_dirs.sort()
            print 'Common subdirectories :', self.common_dirs
        if self.common_funny:
            self.common_funny.sort()
            print 'Common funny cases :', self.common_funny
            
    def report_partial_closure(self): # Print reports on self and on subdirs
        self.report()
        for sd in self.subdirs.itervalues():
            print
            sd.report()

    def report_full_closure(self): # Report on self and subdirs recursively
        self.report()
        for sd in self.subdirs.itervalues():
            print
            sd.report_full_closure()
