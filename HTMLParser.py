from sgmllib import SGMLParser
import htmlentitydefs
import os

def listDirectory(directory, fileExtList):                                         
    "get list of file info objects for files of particular extensions"
    fileList = [os.path.normcase(f) for f in os.listdir(directory)]           
    fileList = [os.path.join(directory, f) for f in fileList if os.path.splitext(f)[1] in fileExtList]
    return fileList

def procString(s):
    return s.strip().strip(' ')

    
class HTMLProcessor(SGMLParser):
    def begin_write(self, ofname):
        self.of = open(ofname, "w")

    def end_write(self):
        self.of.close()
        
    def reset(self):
        self.outstring = ""
        self.begin_trans = 0
        self.is_char_pre = False
        SGMLParser.reset(self)

    def  start_body(self, attrs):
        self.begin_trans = 1

    def end_body(self):
        self.begin_trans = 0
        
    def handle_charref(self, attrs):
        if self.begin_trans == 1:
            attrs.strip()
            self.is_char_pre = True
            #print attrs,
            #self.of.write(str(attrs))

    def handle_data(self, ref):
        if self.begin_trans == 1:
            ref = procString(ref)
            if(len(ref) > 2):
                if(not self.is_char_pre):
                    self.of.write('\n')
                self.of.write(ref)
                self.is_char_pre = False
                
                
if __name__ == "__main__":
    d = 'M:/ÔÓÎÄ/ÍøÂç¶ÁÎï/Áú×å/'
    fl = listDirectory(d, ['.htm'])
    for f in fl:
        fsock = open(f, 'rb')
        strhtml = fsock.read()
        proc = HTMLProcessor()
        proc.begin_write(os.path.splitext(f)[0] + '.txt')
        proc.feed(strhtml)
        proc.end_write()
        proc.close()
        fsock.close()
            
            
