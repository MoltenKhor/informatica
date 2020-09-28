import java.util.Calendar;

public class DatePrinterRunnable implements Runnable{
    public static void main(String args[]){
        Thread dataPrinterTh = new Thread(new DatePrinterRunnable());
        dataPrinterTh.start();
        System.out.println(Thread.currentThread().getName());
    }

    @Override
    public void run(){
        while(true){
            System.out.println(Calendar.getInstance().getTime());
            System.out.println(Thread.currentThread().getName());
            try{
                Thread.sleep(2000);
            }catch(InterruptedException e){
                System.out.println("sleep interrotta");
                return;
            }
        }
    }
}
