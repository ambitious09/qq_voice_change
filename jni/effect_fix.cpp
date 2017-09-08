#include "inc/fmod.hpp"
#include "com_fod_example_EffectUtils.h"
#include <stdlib.h>
#include <unistd.h>
#include <android/log.h>
#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"jason",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"jason",FORMAT,##__VA_ARGS__);
using namespace FMOD;
#define MODE_NORMAL 0
#define MODE_LUOLI 1
#define MODE_DASHU 2
#define MODE_JINGSONG 3
#define MODE_GAOGUAI 4
#define MODE_KONGLING 5
JNIEXPORT void JNICALL Java_com_fod_example_EffectUtils_fix
  (JNIEnv *env, jclass jcls, jstring path_jstr, jint type){
	   System *system;
		Sound *sound;
		Channel *channel;
		DSP *dsp;
		bool playing = true;
		float frequency = 0;
     const char * path_ctsr = env->GetStringUTFChars(path_jstr,NULL);
     LOGI("%s",path_ctsr);
	try {
		//��ʼ��
		System_Create(&system);
		system->init(32, FMOD_INIT_NORMAL, NULL);
		//��������
		system->createSound(path_ctsr, FMOD_DEFAULT, NULL, &sound);
		switch (type) {
		case MODE_NORMAL:
		   //ԭ������
		   system->playSound(sound,0, false, &channel);
		   LOGI("%s","fix normal");
		   break;
		case MODE_LUOLI:
			//�ı������
			//FMOD_DSP_TYPE_PITCHSHIFT dsp���������߽��������õ�һ����Ч
			system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT,&dsp);
//			���������Ĳ���
			dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH,2.5);
			system->playSound(sound,0, false, &channel);
			channel->addDSP(0,dsp);
			 LOGI("%s","fix luoli");
			break;
		case MODE_JINGSONG:
			//��� ��������
			system->createDSPByType(FMOD_DSP_TYPE_TREMOLO,&dsp);
			dsp->setParameterFloat(FMOD_DSP_TREMOLO_FREQUENCY,20);
			 dsp->setParameterFloat(FMOD_DSP_TREMOLO_SKEW,0.5);
		    system->playSound(sound,0, false, &channel);
			channel->addDSP(0,dsp);
			break;
		case MODE_DASHU:
//			�����ĸߵ�
			system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT,&dsp);
			dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH,0.8);
			system->playSound(sound,0, false, &channel);
			channel->addDSP(0,dsp);
			 LOGI("%s","fix dashu");
			break;
		case MODE_GAOGUAI:
			//���
			//���˵�����ٶ�
			system->playSound(sound,0,false,&channel);
			channel->getFrequency(&frequency);
			frequency=frequency*1.6;
			channel->setFrequency(frequency);
			LOGI("%s","fix gaoguai");
			break;
		case MODE_KONGLING:
			system->createDSPByType(FMOD_DSP_TYPE_ECHO,&dsp);
			dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY,300);
			dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK,20);
			system->playSound(sound, 0, false, &channel);
			channel->addDSP(0,dsp);
			LOGI("%s","fix kongling");
			break;
		default:
		   break;
		}

	} catch (...) {
		LOGE("%s","�����쳣");
		goto end;
	}
	system->update();

		//�ͷ���Դ
		//��λ��΢��
		//ÿ�����ж����Ƿ��ڲ���
		while(playing){
			channel->isPlaying(&playing);
			usleep(1000 * 1000);
		}
		goto end;
	end:
		env->ReleaseStringUTFChars(path_jstr,path_ctsr);
		sound->release();
		system->close();
		system->release();

}







