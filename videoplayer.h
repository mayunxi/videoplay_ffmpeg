

#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QThread>
#include <QImage>

extern "C"
{
    #include "libavcodec/avcodec.h"
    #include "libavformat/avformat.h"
    #include "libavutil/pixfmt.h"
    #include "libswscale/swscale.h"
}

//2017.8.10---lizhen
class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;

class VideoPlayer : public QThread
{
    Q_OBJECT

public:
    explicit VideoPlayer();
    ~VideoPlayer();
    bool init();
    void startPlay();

signals:
    void sig_GetOneFrame(QImage); //每获取到一帧图像 就发送此信号
    void sig_GetRFrame(QImage);   ///2017.8.11---lizhen

protected:
    void run();

private:
    QString mFileName;

    //2017.8.10---lizhen
    VlcInstance *_instance;
    VlcMedia *_media;
    VlcMediaPlayer *_player;

    //AVFormatContext - 描述了媒体文件的构成及基本信息，是统领全局的基本结构体，贯穿程序始终，很多函数都要用它作为参数；
    AVFormatContext *pAVFormatContext;
    //AVCodecContext - 描述编解码器上下文的数据结构，包含了众多编解码器需要的参数信息；
    AVCodecContext *pAVCodecContext;
    ///AVCodec - 编解码器对象，每种编解码格式(例如H.264、AAC等）对应一个该结构体，
    /// 如libavcodec/aacdec.c的ff_aac_decoder。每个AVCodecContext中含有一个AVCodec；
    AVCodec *pAVCodec;
    SwsContext *pSwsContext;
    //AVPacket - 存放编码后、解码前的压缩数据，即ES数据；
    AVPacket packet;
    //AVFrame - 存放编码前、解码后的原始数据，如YUV格式的视频数据或PCM格式的音频数据等；
    AVFrame *pAVFrame;

    int videoStreamIndex=-1;
    int videoWidth;
    int videoHeight;

};

#endif // VIDEOPLAYER_H
