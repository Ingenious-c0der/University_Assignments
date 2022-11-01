import java.util.*;
import java.io.*;
import java.net.*;


//sender
public class sender {
    public static void main(String[] args) throws IOException {
        System.out.println("-----SERVER-----");
        System.out.println("Waiting for Connection");
        try {
            InetAddress addr = InetAddress.getByName("localhost");
        } catch (Exception e) {
            System.out.println(e);
        }
        ServerSocket ss = new ServerSocket(500);
        int windowSize = 4 ;
        Socket client = new Socket();
        client = ss.accept();

        BufferedInputStream in = new BufferedInputStream(client.getInputStream());
        DataOutputStream out = new DataOutputStream(client.getOutputStream());

        System.out.println("Received request for sending frames");
        int totalFrameCount = in.read();

        boolean[] f = new boolean[totalFrameCount];

        int errorFrame = in.read();
        System.out.println("Sending...");

        if (errorFrame == 0) {
            for (int i = 0; i < windowSize ; ++i) {
                
                System.out.println("Sending frame number " + i);
                out.write(i);
                out.flush();         
                // System.out.println("Waiting for acknowledgement");
                try {
                    Thread.sleep(3000);
                } catch (Exception e) {
                }
                int ack = in.read();
                if(ack == i)
                {
                    System.out.println("Received acknowledgement for frame " + i + " as " + i);
                     f[ack] = true;
                   
                }
            
            }
            int windowStart = 0;
            for( int i = 0 ; i< totalFrameCount ; i++)
            {
                if(f[i] == false)
                {
                   windowStart = i ;
                   break; 
                }
            }
            int windowEnd = windowSize + windowStart;
            
            while(true)
            {
              
                    if(windowStart > totalFrameCount-1)
                    {
                        break;
                    }
                    System.out.println("Sending frame number " + windowStart);
                    out.write(windowStart);
                    out.flush();
                    try {
                        Thread.sleep(3000);
                    } catch (Exception e) {
                    }
                    ExecutorService service = Executors.newSingleThreadExecutor();

try {
    Runnable r = new Runnable() {
        @Override
        public void run() {
             int ack = in.read();
          
        }
    };

    Future<?> f = service.submit(r);

    f.get(4, TimeUnit.SECONDS);     // attempt the task for four Seconds
}
catch (final InterruptedException e) {
    // The thread was interrupted during sleep, wait or join
}
catch (final TimeoutException e) {
   System.out.println("Timeout on ack for frame " + windowStart);
   System.out.println("Resending frame " + windowStart);
}
catch (final ExecutionException e) {
    // An exception from within the Runnable task
}
finally {
    service.shutdown();
}
                   
                    if(ack == windowStart)
                    {
                        System.out.println("Received acknowledgement for frame " + windowStart + " as " + ack);
                        f[ack] = true;
                         windowStart++;
                         windowEnd++;
                    }
                    
                    
                
            }
            out.flush();
        } else {
            for (int i = 0; i < totalFrameCount; ++i) {
                if (i == errorFrame) {
                    System.out.println("Sending frame no: " + i);

                } else {
                    System.out.println("Sending frame no: " + i);
                    out.write(i);
                    out.flush();
                    System.out.println("Waiting for acknowledgement ");
                    try {
                        Thread.sleep(2000);
                    } catch (Exception e) {
                    }
                    int a = in.read();
                    if (a != 255) {
                        System.out.println("Received ack for frame no: " + i + " as" + a);
                        f[i] = true;

                    }
                    else
                    {
                        break;
                    }
                }
            }

            for (int a = 0; a < totalFrameCount; ++a) {
                if (f[a] == false) {
                    System.out.println("Resending frame " + a);
                    out.write(a);
                    out.flush();
                    System.out.println("Waiting for ack");
                    try {
                        Thread.sleep(5000);
                    } catch (Exception e) {
                    }
                    int b = in.read();
                    System.out.println("Received ack for frame no: " + a + " as" + b);
                    f[a] = true;
                }
            }
            out.flush();
        }
        in.close();
        out.close();
        System.out.println("Quitting");
    }
}