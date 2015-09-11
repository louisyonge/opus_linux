package testJNI;
import java.nio.ByteBuffer;

import top.oply.opuslib.OpusTool;
public class Demo {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		OpusTool tool = new OpusTool();
        String s = tool.nativeGetString();
        System.out.println(s);
        
        String curDir = System.getProperty("user.dir");
        
        String fin = curDir + "/src/jni/audioFile/test.opus";
        String fout = fin + ".output.opus";
        
        ByteBuffer buf = tool.decode(fin, null);
        tool.encode(buf, fout, null);
        
        tool.releaseByteBuffer(buf);
        System.out.println("\n" + fout);
	}

}
