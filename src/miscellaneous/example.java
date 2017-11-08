import java.util.Scanner;

class example
{
    final static int BSIZE = 524288;
    static byte[] buffer = new byte[BSIZE];
    static int p = BSIZE;

    static byte readByte()
    {
        if (p==BSIZE) {
            try {
                System.in.read(buffer); p=0;
            } catch (Exception e) {
                return ' ';
            }
        }
        return buffer[p++];
    }
    public static void main(String[] args)
    {
        Scanner in = new Scanner(System.in);
        int T = in.nextInt();
        while (T --> 0) {
            String str = in.next();
            if (str.matches("[A-F]?A+F+C+[A-F]?"))
                System.out.println("Infected!");
            else
                System.out.println("Good");
        }
    }
}
