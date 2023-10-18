import java.net.*;
import java.io.*;

public class Client {
    public static void main(String[] args) {
        try {
            Socket socket = new Socket("localhost", 9001);
            OutputStream outputStream = socket.getOutputStream();
            PrintWriter output = new PrintWriter(outputStream, true);
            BufferedReader inputReader = new BufferedReader(new InputStreamReader(System.in));

            System.out.println("[JAVA CLIENT] Connection established.");

            System.out.print("[JAVA CLIENT] Enter 1st number to be sent to the Server: ");
            String n1 = inputReader.readLine();
            output.println(n1);
            System.out.print("[JAVA CLIENT] Enter 2nd number to be sent to the Server: ");
            String n2 = inputReader.readLine();
            output.println(n2);

            InputStream is = socket.getInputStream();
            BufferedReader in = new BufferedReader(new InputStreamReader(is));
            String sum1 = in.readLine();

            System.out.println("[JAVA CLIENT] Sum received from server: " + sum1);

            socket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}



    /*
    public static void main(String[] args) {

        Socket s = null;
        InputStreamReader isr = null;
        OutputStreamWriter osr = null;
        BufferedWriter bw = null;
        BufferedReader br = null;

        try {
            s = new Socket("localhost", 9001);

            isr = new InputStreamReader(s.getInputStream());
            osr = new OutputStreamWriter(s.getOutputStream());

            br = new BufferedReader(isr);
            bw = new BufferedWriter(osr);

            Scanner scan = new Scanner(System.in);

            while (true) {
                String msg2send = scan.nextLine();

                bw.write(msg2send);
                bw.newLine();
                bw.flush();

                System.out.println("Server: " + br.readLine());

                if (msg2send.equalsIgnoreCase("BYE"))
                    break;

            }
        }

        catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                if (s != null)
                    s.close();

                if (isr != null)
                    isr.close();

                if (osr != null)
                    osr.close();

                if (br != null)
                    br.close();

                if (bw != null)
                    bw.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
*/

/*
 * import java.io.BufferedReader;
 * import java.io.IOException;
 * import java.io.InputStreamReader;
 * import java.io.PrintWriter;
 * import java.net.*;
 * 
 * public class client_program1
 * {
 * 
 * public static void main(String[] args) throws IOException
 * {
 * Socket s = new Socket("127.0.0.1",9080);
 * 
 * PrintWriter output = new PrintWriter(s.getOutputStream(),true);
 * output.println("From Java Client...");
 * 
 * BufferedReader input = new BufferedReader(new
 * InputStreamReader(s.getInputStream()));
 * System.out.println(input.readLine());
 * }
 * }
 */