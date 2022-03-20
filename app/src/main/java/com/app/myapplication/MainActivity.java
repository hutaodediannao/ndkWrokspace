package com.app.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import com.app.myapplication.databinding.ActivityMainBinding;

import java.util.Arrays;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MainActivity";

    static {
        System.loadLibrary("native-lib");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
    }

    public native void testPthread(int data);

    public native void testPthread2();

    public void updateUI(int data) {
        Log.i(TAG, "线程回调成功");
        Toast.makeText(this, "调用成功: " + data, Toast.LENGTH_SHORT).show();
    }

    public native void listToJNI(List<String> strList);

    private native void updatePerson(Person p, String newName);

    private native void updatePerson2(Person p, String newName);

    private native void updatePerson3(Person p3, Person.AddRess ad);

    private native int testIncludeLibrary(int a, int b);

    public void test(View view) {
        binding.tvTerminal.setText("");
        switch (view.getId()) {
            case R.id.button0:
                testPthread(200);
                binding.tvTerminal.append("更新成功\n");
                break;
            case R.id.button1:
                listToJNI(Arrays.asList("nokia", "oppo", "mi", "huawei"));
                binding.tvTerminal.append("更新成功\n");
                break;
            case R.id.button2:
                testPthread2();
                binding.tvTerminal.append("更新成功\n");
                break;
            case R.id.button3:
                Person p = new Person("胡涛", 32);
                updatePerson(p, "呆梨");
                Log.i(TAG, p.toString());
                binding.tvTerminal.append("更新成功\n");
                break;
            case R.id.button4:
                Person p2 = new Person("胡涛", 32);
                updatePerson2(p2, "呆梨2");
                Log.i(TAG, p2.toString());
                binding.tvTerminal.append("更新成功\n");
                break;
            case R.id.button5:
                Person p3 = new Person("胡涛", 32);
                Person.AddRess ad = new Person.AddRess("湖北省", "黄冈市", 4001);
                updatePerson3(p3, ad);
                Log.i(TAG, p3.toString());
                binding.tvTerminal.append("更新成功\n");
                break;
            case R.id.button6:
                int sum = testIncludeLibrary(1, 3);
                Log.i(TAG, "sum ======> 1+3=>=" + sum);
                binding.tvTerminal.append("更新成功\n");
                break;
            case R.id.button7:
                DynamicJNI dy = new DynamicJNI();
                String testStr = dy.getNativeString();
                int s = dy.sum(3, 5);
                Log.i(TAG, "函数的动态注册 testStr======> " + testStr + ", sum=" + s);
                binding.tvTerminal.append(testStr + "\n");
                binding.tvTerminal.append("DynamicJNI.sum(3,5)=" + s + "\n");
                binding.tvTerminal.append("更新成功\n");
                break;
            default:
                break;
        }
    }


}