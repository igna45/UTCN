package Utils;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintStream;

public class Log {
    private PrintStream out;

    public Log(String fileName) throws FileNotFoundException {
        out = new PrintStream(new FileOutputStream(fileName));
    }

    public void log(String message) {
        out.println(message);
    }

    public void close() {
        out.close();
    }
}