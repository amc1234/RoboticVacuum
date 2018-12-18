package roboticvacuum.roboticvacuum;

import android.os.Bundle;
import android.app.Activity;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class MainActivity extends Activity {
    RelativeLayout layout_joystick1, layout_joystick2;
    ImageView image_joystick, image_border;
    TextView textView1, textView2, textView3, textView4, textView5;

    JoyStickClass js1, js2;

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        textView1 = (TextView)findViewById(R.id.textView1);
        textView2 = (TextView)findViewById(R.id.textView2);
        textView3 = (TextView)findViewById(R.id.textView3);
        textView4 = (TextView)findViewById(R.id.textView4);
        textView5 = (TextView)findViewById(R.id.textView5);

        layout_joystick1 = (RelativeLayout)findViewById(R.id.layout_joystick1);
        layout_joystick2 = (RelativeLayout)findViewById(R.id.layout_joystick2);

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

        layout_joystick1.setOnTouchListener(new OnTouchListener() {
            public boolean onTouch(View arg0, MotionEvent arg1) {
                js1.drawStick(arg1);
                if(arg1.getAction() == MotionEvent.ACTION_DOWN || arg1.getAction() == MotionEvent.ACTION_MOVE) {

                    int direction = js1.get8Direction();
                    if(direction == JoyStickClass.STICK_UP) {
                    } else if(direction == JoyStickClass.STICK_UPRIGHT) {
                    } else if(direction == JoyStickClass.STICK_RIGHT) {
                    } else if(direction == JoyStickClass.STICK_DOWNRIGHT) {
                    } else if(direction == JoyStickClass.STICK_DOWN) {
                    } else if(direction == JoyStickClass.STICK_DOWNLEFT) {
                    } else if(direction == JoyStickClass.STICK_LEFT) {
                    } else if(direction == JoyStickClass.STICK_UPLEFT) {
                    } else if(direction == JoyStickClass.STICK_NONE) {
                    }
                } else if(arg1.getAction() == MotionEvent.ACTION_UP) {
                }
                return true;
            }
        });

        layout_joystick2.setOnTouchListener(new OnTouchListener() {
            public boolean onTouch(View arg0, MotionEvent arg1) {
                js2.drawStick(arg1);
                if(arg1.getAction() == MotionEvent.ACTION_DOWN || arg1.getAction() == MotionEvent.ACTION_MOVE) {
                    int direction = js2.get8Direction();
                    if(direction == JoyStickClass.STICK_UP) {
                    } else if(direction == JoyStickClass.STICK_UPRIGHT) {
                    } else if(direction == JoyStickClass.STICK_RIGHT) {
                    } else if(direction == JoyStickClass.STICK_DOWNRIGHT) {
                    } else if(direction == JoyStickClass.STICK_DOWN) {
                    } else if(direction == JoyStickClass.STICK_DOWNLEFT) {
                    } else if(direction == JoyStickClass.STICK_LEFT) {
                    } else if(direction == JoyStickClass.STICK_UPLEFT) {
                    } else if(direction == JoyStickClass.STICK_NONE) {
                    }
                } else if(arg1.getAction() == MotionEvent.ACTION_UP) {

                }
                return true;
            }
        });
    }
}
