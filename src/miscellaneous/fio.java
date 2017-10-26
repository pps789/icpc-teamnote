static class fio
{
    final private int BSIZE=524288;
    private byte[] buffer = new byte[BSIZE];
    private int p = BSIZE;
    private InputStream in;
    public fio()
    {
        in=System.in;
    }
    public byte readByte() throws IOException
    {
        if(p==BSIZE)
        {
            in.read(buffer);
            p=0;
        }
        return buffer[p++];
    }
    public int readInt() throws IOException
    {
        byte b = readByte();
        while (( b < '0' || b > '9') && b != '-') {
          b = readByte();
        }
        int ret=0; boolean neg = b == '-';
        if (neg) b = readByte();
        while (b >= '0' && b <= '9') {
          ret = ret * 10 + b - '0';
          b = readByte();
        }
        return neg ? -ret : ret;
    }
}
