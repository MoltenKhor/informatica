import java.util.Calendar;

public class DatePrinterThread extends Thread{
    public static void main(String args[]){
        DatePrinterThread dataPrinterTh = new DatePrinterThread();
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
