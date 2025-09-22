class MonoThread extends Thread {
    private String chaine;

    public MonoThread(String chaine) {
        this.chaine = chaine;
    }

    public void run() {
        System.out.println(chaine);
    }
}

public class Monotache {

    public static void main(String[] args) {
        String[] chaines = {
            "1 Souvent, pour s’amuser, les hommes d’équipage",
            "2 Prennent des goélands, vastes oiseaux des mers,",
            "3 Qui suivent, indolents compagnons de voyage,",
            "4 Le navire glissant sur les gouffres amers",
            "5 Souvent, pour s’amuser, les hommes d’équipage",
            "6 Prennent des goélands, vastes oiseaux des mers,",
            "7 Qui suivent, indolents compagnons de voyage,",
            "8 Le navire glissant sur les gouffres amers",
        };
        MonoThread[] threads = new MonoThread[chaines.length];
        for (int i = 0; i < chaines.length; i++) {
            threads[i] = new MonoThread(chaines[i]);
            threads[i].start();
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

    }
}
