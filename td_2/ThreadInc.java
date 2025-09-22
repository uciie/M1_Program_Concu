public class ThreadInc extends Thread {
    private Variable var;
    private final int N;
    private final int inc_dec; // 1 pour inc, -1 pour dec

    public ThreadInc(int N, int inc_dec, Variable var) {
        this.var = var;
        this.N = N;
        this.inc_dec = inc_dec;
    }

    public void run() {
        for (int i = 0; i < N; i++) {
            var.inc(inc_dec);
        }
    }
}