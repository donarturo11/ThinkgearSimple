#include <cstdio>
#include "Thinkgear.h"


// stream parser callback
// check code definitions in ThinkGearStreamParser.h
void tgHandleStreamDataValueFunc( unsigned char extendedCodeLevel, unsigned char code, unsigned char valueLength, const unsigned char *value, void *customData){
    ThinkGear& tg = *reinterpret_cast<ThinkGear*>(customData);
    if (extendedCodeLevel == 0){
        //if(code != PARSER_CODE_RAW_SIGNAL) printf("%#x\n",code);//, code, code, code);
        //std::cout << extendedCodeLevel;
        switch (code) {
            case PARSER_CODE_BATTERY:
                
                tg.values.battery = value[0] & 0xff;
                //ofNotifyEvent(tg.onBattery, tg.values);
                break;
            case PARSER_CODE_POOR_QUALITY:
                tg.values.poorSignal = value[0] & 0xff;
                //ofNotifyEvent(tg.onPoorSignal, tg.values);
                break;
            case PARSER_CODE_ATTENTION:
                tg.values.attention = value[0] & 0xff;
                //ofNotifyEvent(tg.onAttention, tg.values);
                break;
            case PARSER_CODE_MEDITATION:
                tg.values.meditation = value[0] & 0xff;
                //ofNotifyEvent(tg.onMeditation, tg.values);
                break;
            case 0x16:
                tg.values.blinkStrength = value[0] & 0xff;
                //ofNotifyEvent(tg.onBlinkStrength, tg.values);
            case( 0xd4 ):
                // printf("Standby... autoconnecting\n");
                if(tg.allowRawDataEvents) ofNotifyEvent(tg.onConnecting, tg.values);
                tg.device->writeByte((unsigned char) 0xc2); // what is this?
                break;
            case( 0xd0 ):
                ofNotifyEvent(tg.onReady, tg.values);
                break;
            case( 0xd1 ):
                {
                    //ofMessage err("Headset not found");
                    //ofNotifyEvent(tg.onError, err);
                }
                break;
            case PARSER_CODE_RAW_SIGNAL:
                tg.values.raw = (value[0] << 8) | value[1];
                ofNotifyEvent(tg.onRaw, tg.values);
                break;
            case PARSER_CODE_ASIC_EEG_POWER_INT:
                {
                    //
                    //131?
                    //eegPower[j] = ((unsigned long)packetData[++i] << 16) | ((unsigned long)packetData[++i] << 8) | (unsigned long)packetData[++i];
                    
                    /*int v = 0;
                    for (int i = 0; i < 24; i+=3) {
                        v = (value[i] * 255 * 255) + (value[i + 1] * 255) + (value[i + 2]);
                        std::cout << "a: " << v;
                    }*/
                    
                    int pos = 0;
                    tg.values.eegDelta = (value[pos] << 16) | (value[pos+1] << 8) | (value[pos+2]); pos += 3;
                    tg.values.eegTheta = (value[pos] << 16) | (value[pos+1] << 8) | (value[pos+2]); pos += 3;
                    tg.values.eegLowAlpha = (value[pos] << 16) | (value[pos+1] << 8) | (value[pos+2]); pos += 3;
                    tg.values.eegHighAlpha = (value[pos] << 16) | (value[pos+1] << 8) | (value[pos+2]); pos += 3;
                    tg.values.eegLowBeta = (value[pos] << 16) | (value[pos+1] << 8) | (value[pos+2]); pos += 3;
                    tg.values.eegHighBeta = (value[pos] << 16) | (value[pos+1] << 8) | (value[pos+2]); pos += 3;
                    tg.values.eegLowGamma = (value[pos] << 16) | (value[pos+1] << 8) | (value[pos+2]); pos += 3;
                    tg.values.eegHighGamma = (value[pos] << 16) | (value[pos+1] << 8) | (value[pos+2]); pos += 3;
                    
                    std::cout << "b: " << tg.values.eegDelta << std::endl;
                    std::cout << "b: " << tg.values.eegTheta << std::endl;
                    std::cout << "b: " << tg.values.eegLowAlpha << std::endl;
                    std::cout << "b: " << tg.values.eegHighAlpha << std::endl;
                    std::cout << "b: " << tg.values.eegLowBeta << std::endl;
                    std::cout << "b: " << tg.values.eegHighBeta << std::endl;
                    std::cout << "b: " << tg.values.eegLowGamma << std::endl;
                    std::cout << "b: " << tg.values.eegMidGamma << std::endl;
                    std::cout << "\n";
                    //ofNotifyEvent(tg.onEeg, tg.values);
                    break;
                }
            /* Other [CODE]s */
            default:
                printf( "EXCODE level: %d CODE: 0x%02X vLength: %d\n", extendedCodeLevel, code, valueLength );
                printf( "Data value(s):" );
                for( int i=0; i<valueLength; i++ ) printf( " %02X", value[i] & 0xFF );
                printf( "\n" );
                break;
        }
    }
}


// similar to stream callback
void Thinkgear::tgHandleCommsDriverDataValueFunc(int code, float value) {

    switch (code) {
        case TG_DATA_BATTERY:
            values.battery = value;
            //ofNotifyEvent(onBattery, values);
            break;
        case TG_DATA_POOR_SIGNAL:
            values.poorSignal = value;
            //ofNotifyEvent(onPoorSignal, values);
            break;
        case TG_DATA_ATTENTION:
            values.attention = value;
            //ofNotifyEvent(onAttention, values);
            break;
        case TG_DATA_MEDITATION:
            values.meditation = value;
            //ofNotifyEvent(onMeditation, values);
            break;
        case TG_DATA_BLINK_STRENGTH:
            values.blinkStrength = value;
            //ofNotifyEvent(onBlinkStrength, values);
            break;
        case TG_DATA_RAW:
            values.raw = value;
            //ofNotifyEvent(onRaw, values);
            break;
        case TG_DATA_DELTA:
            values.eegDelta = value;
            break;
        case TG_DATA_THETA:
            values.eegTheta = value;
            break;
        case TG_DATA_ALPHA1:
            values.eegLowAlpha = value;
            break;
        case TG_DATA_ALPHA2:
            values.eegHighAlpha = value;
            break;
        case TG_DATA_BETA1:
            values.eegLowBeta = value;
            break;
        case TG_DATA_BETA2:
            values.eegHighBeta = value;
            break;
        case TG_DATA_GAMMA1:
            values.eegLowGamma = value;
            break;
        case TG_DATA_GAMMA2:
            values.eegHighGamma = value;
            
            // after 8th band is received notify
            //ofNotifyEvent(onEeg, values);
            break;
            
        default:
            break;
    }
}

Thinkgear::Thinkgear() : isReady(false) {
    
    device = new ofSerial();
    // print all devices to console
    device->listDevices();
    allowRawDataEvents = false;
    parserSetup = false;
    attempts = 0;
    unavailableCount = 0;
    noConnectionRestartCount = 250;
    noDataRestartCount = 500;
    connectionType = TG_STREAM_PARSER;
}

Thinkgear::~Thinkgear(){
    close();
}

void Thinkgear::setup(string deviceName, int baudRate, ThinkGearImplementation connectionType) {
    this->deviceName = deviceName;
    this->baudRate = baudRate;
    this->connectionType = connectionType;
    
    if(connectionType == TG_COMMS_DRIVER) {
		#ifdef TARGET_OSX
        driver.setup(deviceName, baudRate,this,&ofxThinkgear::tgHandleCommsDriverDataValueFunc);
        if(driver.isReady) isReady = true;
		#endif
    } else {
        std::cerr << "Blinks cannot be activated in TG_STREAM_PARSER mode.\n";
    }
}

void Thinkgear::close(){
    
    if(connectionType == TG_STREAM_PARSER) {
        if (isReady){
            //device->writeByte(0xC1);
            device->flush();
            //device.drain();
            device->close();
            isReady = false;
        }
    }    
    
    delete device;
    device = NULL;
}

//int unavailableCount = 0;

void Thinkgear::idle() {
    
    if(connectionType == TG_STREAM_PARSER) {
        if (isReady) {
            int n = device->available();
            if (n > 0){
                //unavailableCount = 0;
                n = device->readBytes(buffer, min(n,512));
            }
        }
    }
    
}

void Thinkgear::update(){
    
    if(connectionType == TG_COMMS_DRIVER) {
        #ifdef TARGET_OSX
        driver.update();
        isReady = driver.isReady;
        if(!isReady && ofGetFrameNum() % noConnectionRestartCount == 0) {
            std::cerr << "connecting to device...\n";
            attempts++;
            if(driver.connect()) {
                std::cerr << "ThinkGear device setup\n";
                attempts = 0;
            }
        }
		#endif
        
    } else if(connectionType == TG_STREAM_PARSER) {
        
        if (!isReady && ofGetFrameNum() % noConnectionRestartCount == 0){
            std::cerr << "connecting to device...\n";
            attempts++;
            if (device->setup(deviceName, baudRate)){
                device->flush();
                int parserInited = THINKGEAR_initParser(&parser, PARSER_TYPE_PACKETS, tgHandleStreamDataValueFunc, this);
                ofLogVerbose() << "parser setup: " << parserInited;;
                isReady = true;
                ofLogVerbose() << "ThinkGear device setup";
                attempts = 0;
            }
            
        }
        if (!isReady)
            return;
        int n = device->available();
        if (n > 0){
            unavailableCount = 0;
            n = device->readBytes(buffer, min(n,512));
            for (int i=0; i<n; ++i){
                THINKGEAR_parseByte(&parser, buffer[i]);
            }
        } else {
            
            // reconnection problems fix (connected but no data). made device a pointer that gets deleted and reassigned
            // test by switching device off/on
            unavailableCount++;
            if(unavailableCount >  noDataRestartCount) {
                ofLogVerbose() << "*** no data available - attempt to reconnect";
                isReady = false;
                attempts = 0;
                unavailableCount = 0;
                device->close();
                delete device;
                device = NULL;
                
                ofSerial* retryDevice = new ofSerial();
                device = retryDevice;
            }
        }
        
    }
    
    
}

void Thinkgear::flush(){
    if(connectionType == TG_STREAM_PARSER) {
        if (isReady) device->flush();            
    }
}

