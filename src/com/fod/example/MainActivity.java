package com.fod.example;

import java.io.File;

import org.fmod.FMOD;


import android.app.Activity;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.View;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		FMOD.init(this);
		setContentView(R.layout.activity_main);
	}
	public void mFix(View  btn){
		String path = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separatorChar + "tts.wav";
		Log.d("jason", "mFix");
		switch (btn.getId()) {
		case R.id.btn_normal:
			EffectUtils.fix(path, EffectUtils.MODE_NORMAL);
			break;
			
		case R.id.btn_luoli:
			EffectUtils.fix(path, EffectUtils.MODE_LUOLI);
			break;	
			
		case R.id.btn_dashu:
			EffectUtils.fix(path, EffectUtils.MODE_DASHU);
			break;	
			
		case R.id.btn_jingsong:
			EffectUtils.fix(path, EffectUtils.MODE_JINGSONG);
			break;	
			
		case R.id.btn_gaoguai:
			EffectUtils.fix(path, EffectUtils.MODE_GAOGUAI);
			break;	
			
		case R.id.btn_kongling:
			EffectUtils.fix(path, EffectUtils.MODE_KONGLING);
			break;		

		default:
			break;
		}
	}
	
	
	@Override
	protected void onDestroy() {
		super.onDestroy();
		FMOD.close();
	}
}
