package dc.com.developercomunity;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void exDesarrollador(View view){
        Intent dev=new Intent(this,Desarrollador.class);//Intento

        startActivity(dev);//Iniciar actividad especificando el intento(i)
    }

    public void exVisitante(View view){
        Intent vis=new Intent(this,Visitante.class);
        startActivity(vis);
    }

    public void exCliente(View view){
        Intent cli=new Intent(this,Cliente.class);
        startActivity(cli);
    }
}
