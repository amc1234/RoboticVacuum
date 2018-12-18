package roboticvacuum.roboticvacuum;

import android.os.Bundle;
import android.app.Activity;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.RelativeLayout;
import android.widget.Switch;

public class MainActivity extends Activity {
    RelativeLayout layout_joystick1, layout_joystick2;
    Switch toggle_vacuum;

    JoyStickClass js1, js2;

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        layout_joystick1 = (RelativeLayout) findViewById(R.id.layout_joystick1);
        layout_joystick2 = (RelativeLayout) findViewById(R.id.layout_joystick2);
        toggle_vacuum = (Switch) findViewById(R.id.toggle_vacuum);

        js1 = new JoyStickClass(getApplicationContext(), layout_joystick1, R.drawable.image_button);
        js1.setStickSize(75, 75);
        js1.setLayoutSize(150, 150);
        js1.setLayoutAlpha(150);
        js1.setStickAlpha(100);
        js1.setOffset(35);
        js1.setMinimumDistance(50);

        js2 = new JoyStickClass(getApplicationContext(), layout_joystick2, R.drawable.image_button);
        js2.setStickSize(75, 75);
        js2.setLayoutSize(150, 150);
        js2.setLayoutAlpha(150);
        js2.setStickAlpha(100);
        js2.setOffset(35);
        js2.setMinimumDistance(50);

        setupListener();
    }

    void setupListener() {
        toggle_vacuum.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if(toggle_vacuum.isChecked()) {
                    // TODO: turn on vacuum
                }
                else {
                    // TODO: turn off vacuum
                }
            }
        });

        layout_joystick1.setOnTouchListener(new OnTouchListener() {
            public boolean onTouch(View arg0, MotionEvent arg1) {
                js1.drawStick(arg1);
                changeSpeed(getSpeed(js1.getY()), getSpeed(js2.getY()));
                return true;
            }
        });

        layout_joystick2.setOnTouchListener(new OnTouchListener() {
            public boolean onTouch(View arg0, MotionEvent arg1) {
                js2.drawStick(arg1);
                changeSpeed(getSpeed(js1.getY()), getSpeed(js2.getY()));
                return true;
            }
        });
    }

    float getSpeed(float jsMag) {
        return jsMag;
    }

    void changeSpeed(float v1, float v2) {
//        Log.d("f", "changeSpeed: " + String.valueOf(v1) + String.valueOf(v2));
        // TODO: change speed
    }
}
