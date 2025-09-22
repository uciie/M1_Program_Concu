public class MonThread extends Thread { 
    private final int id;
    private final int N;
    private final int K;
    private float max = 0;
    private int max_x = 0;
    private int max_y = 0;

    double f(int x, int y) {
        return x * x * x * Math.sin((double)x) - y * y * y * Math.cos((double)y) + x * y * y;
    }

    public MonThread(int id, int N, int K) {
        this.id = id;
        this.N = N;
        this.K = K;
    }

    public void run() { 
        int i;
        i = this.id;
        System.out.printf("demmarage de la thread %d\n", i);
        for (int x = i; x <= N; x += K)
        {
            for (int y = 0; y <= N; y++)
            {
                float cal = (float ) f(x, y);
                if (Math.abs(cal) > max)
                {
                    max = cal;
                    max_x = x;
                    max_y = y;
                }
            }
        }
    } 

    public float getMax() {
        return max;
    }

    public int getMaxX() {
        return max_x;
    }

    public int getMaxY() {
        return max_y;
    }
}