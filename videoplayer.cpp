/**
 * 李震
 * 我的码云：https://git.oschina.net/git-lizhen
 * 我的CSDN博客：http://blog.csdn.net/weixin_38215395
 * 联系：QQ1039953685
 */

#include "videoplayer.h"
#include <QTime>
#include <QDebug>


#include <stdio.h>
#include<iostream>
using namespace std;
VideoPlayer::VideoPlayer()
{

}

VideoPlayer::~VideoPlayer()
{




}

bool VideoPlayer::init()
{
    av_register_all();         //初始化FFMPEG  调用了这个才能正常适用编码器和解码器
    avformat_network_init();   //初始化网络流格式,使用RTSP网络流时必须先执行
    //Allocate an AVFormatContext.
    pAVFormatContext = avformat_alloc_context();//申请一个AVFormatContext结构的内存,并进行简单初始化

    //下面是公共的RTSP测试地址
    char m_str_url[]="rtsp://218.204.223.237:554/live/1/0547424F573B085C/gsfp90ef4k0a6iap.sdp";
    //QString m_str_url="rtsp://admin:stfz2430@192.168.1.64:554/h264/main/av_stream";
    AVDictionary *avdic=NULL;
    av_dict_set(&avdic, "rtsp_transport",  "tcp", 0); //rtsp默认采用UDP,容易丢包，造成花屏，这里改为TCP
    av_dict_set(&avdic,"max_delay","100",0);//设置最大延时

    //媒体文件的构成及基本信息
    int result=avformat_open_input(&pAVFormatContext,m_str_url,nullptr,&avdic);
    if (result<0){
        qDebug()<<"打开视频流失败";
        return false;
    }

    //获取视频流信息
    result=avformat_find_stream_info(pAVFormatContext,nullptr);
    if (result<0){
        qDebug()<<"获取视频流信息失败";
        return false;
    }

    //获取视频流索引
    for (uint i = 0; i < pAVFormatContext->nb_streams; i++) {
        if (pAVFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStreamIndex = i;
            break;
        }
    }

    if (videoStreamIndex==-1){
        qDebug()<<"获取视频流索引失败";
        return false;
    }

    //获取编解码器上下文
    pAVCodecContext = pAVFormatContext->streams[videoStreamIndex]->codec;
    //获取视频流的分辨率大小
    videoWidth=pAVCodecContext->width;
    videoHeight=pAVCodecContext->height;

    //获取视频流解码器
    pAVCodec = avcodec_find_decoder(pAVCodecContext->codec_id);

    pSwsContext = sws_getContext(videoWidth,videoHeight,AV_PIX_FMT_YUV420P,videoWidth,videoHeight,AV_PIX_FMT_RGB24,SWS_BICUBIC,0,0,0);

    //打开对应解码器
    result=avcodec_open2(pAVCodecContext,pAVCodec,NULL);
    if (result<0){
        qDebug()<<"打开解码器失败";
        return false;
    }

    qDebug()<<"初始化视频流成功";
    return true;

}

void VideoPlayer::startPlay()
{
    ///调用 QThread 的start函数 将会自动执行下面的run函数 run函数是一个新的线程
    this->start();

}

void VideoPlayer::run()
{

    int ret, got_picture;
    AVPicture  pAVPicture;
    avpicture_alloc(&pAVPicture,AV_PIX_FMT_RGB24,videoWidth,videoHeight);

    pAVFrame=av_frame_alloc();
    while (1)
    {
        //
        if (av_read_frame(pAVFormatContext, &packet) < 0)
        {
            break; //这里认为视频读取完了
        }
        //只解析视频流
        if (packet.stream_index == videoStreamIndex)
        {
            ///fwrite(packet->data,1,packet->size,fpSave);//can写数据到h264文件中
            QTime time;
            time.start();
            ret = avcodec_decode_video2(pAVCodecContext, pAVFrame, &got_picture,&packet);

            if (ret < 0) {
                qDebug("decode error.");
            }

            if (got_picture) {
                sws_scale(pSwsContext,(const uint8_t* const *)pAVFrame->data,pAVFrame->linesize,0,videoHeight,pAVPicture.data,pAVPicture.linesize);

                QImage tmpImg(pAVPicture.data[0],videoWidth,videoHeight,QImage::Format_RGB888);
                QImage image = tmpImg.copy(); //把图像复制一份 传递给界面显示
                emit sig_GetOneFrame(image);  //发送信号

                //提取出图像中的R数据
                for(int i=0;i<pAVCodecContext->width;i++)
                {
                    for(int j=0;j<pAVCodecContext->height;j++)
                    {
                        QRgb rgb=image.pixel(i,j);
                        int r=qRed(rgb);
                        image.setPixel(i,j,qRgb(r,0,0));
                    }
                }
                emit sig_GetRFrame(image);
            }
            qDebug( "decode time = %d ms\n",time.elapsed());
        }
        av_free_packet(&packet); //释放资源,否则内存会一直上升

        //msleep(0.02); //停一停  不然放的太快了
    }
    avcodec_close(pAVCodecContext);
    avformat_close_input(&pAVFormatContext);
}
