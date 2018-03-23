#include "x264_to_mp4.h"
using namespace std;
MyMuxer::MyMuxer(int32_t width,int32_t height,const char *filename):width_(width),height_(height),filename_(filename){

}

AVStream* MyMuxer::add_stream(AVFormatContext *ofmt_ctx, AVCodec **codec, enum AVCodecID codec_id, uint8_t *data, int data_size)
{
    AVCodecContext *codec_ctx;
    AVStream *out_stream;
    *codec = avcodec_find_encoder(codec_id);

    out_stream = avformat_new_stream(ofmt_ctx,*codec);
    ofmt_ctx->streams[0]->time_base.den  = 10000;
    ofmt_ctx->streams[0]->time_base.num  = 1;
    out_stream->id = ofmt_ctx->nb_streams-1;


    codec_ctx = out_stream->codec;
    vi_=out_stream->index;
    codec_ctx->codec_id = AV_CODEC_ID_H264;
    codec_ctx->width = width_;
    codec_ctx->height = height_;
    codec_ctx->time_base.den = 1000;//fenmu
    codec_ctx->time_base.num = 1;//fenzi
    codec_ctx->gop_size = 1;
    codec_ctx->pix_fmt = AV_PIX_FMT_YUV420P;
    codec_ctx->extradata = data;
    codec_ctx->extradata_size = data_size;
    if(ofmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
        codec_ctx->flags |= CODEC_FLAG_GLOBAL_HEADER;
    return out_stream;
}

void MyMuxer::write_h264(uint8_t *data,int lenght,bool keyframe,int32_t timestamp_ms)
{
    int ret =0;
    AVStream *out_stream = ofmt_ctx_->streams[vi_];
    AVPacket pkt;
    AVCodecContext *codec_ctx = out_stream->codec;

    av_init_packet(&pkt);
    pkt.data = data;
    pkt.size = lenght;
    pkt.stream_index = out_stream->index;
    pkt.pts = av_rescale_q(timestamp_ms, codec_ctx->time_base,out_stream->time_base);
    pkt.dts = pkt.pts;
    pkt.duration =av_rescale_q(pkt.duration,codec_ctx->time_base,out_stream->time_base);
    pkt.pos = -1;
    pkt.flags = keyframe ? AV_PKT_FLAG_KEY : 0;

    ret = av_interleaved_write_frame(ofmt_ctx_,&pkt);
    if(ret < 0)
        cout<<"write mp4 fail"<<endl;
    av_free_packet(&pkt);
}
void MyMuxer::tran_open(int32_t width,int32_t height,char *filename,uint8_t *data,int data_size)
{
    width_ = width;
    height_ = height;
    filename_ = filename;

    int ret=0;
    av_register_all();

    avformat_alloc_output_context2(&ofmt_ctx_,NULL,NULL,filename_);

    ofmt_ = ofmt_ctx_->oformat;
    if(ofmt_->video_codec!= AV_CODEC_ID_NONE)
    {
        ofmt_->video_codec = AV_CODEC_ID_H264;
        out_stream_ = add_stream(ofmt_ctx_,&codec_,ofmt_->video_codec,data,data_size);
    }


    if(!(ofmt_->flags & AVFMT_NOFILE))
    {
        ret = avio_open(&ofmt_ctx_->pb,filename_,AVIO_FLAG_WRITE);
    }
    if(ret<0)
    {
        cout<<"open file fail"<<endl;
    }


    ret = avformat_write_header(ofmt_ctx_,NULL);
    if(ret < 0)
    {
        cout<<"write header failed"<<endl;
    }
}
void MyMuxer::closemp4()
{
       av_write_trailer(ofmt_ctx_);
       avformat_free_context(ofmt_ctx_);
}










/*
 * AVOutputFormat *ofmt = NULL;//out struct
    AVFormatContext *ifmt_ctx_v = NULL,*ofmt_ctx = NULL;
    AVPacket pkt;
    int ret,i;
    int videoindex_v = 0,videoindex_out = 0;
    int frame_index = 0;
    int64_t cur_pts_v = 0,cur_pts_a = 0;
    const char *input_filename_a = "/home/chengfei/h264_512_512.h264";
    const char *out_filename = "/home/chengfei/h264_512_512.mp4";
    av_register_all();

    if((ret = avformat_open_input(&ifmt_ctx_v,input_filename_a,0,0)) < 0)
    {
        cout<<"avformat_open_input"<<endl;
    }
    if((ret = avformat_find_stream_info(ifmt_ctx_v,0)) < 0)
    {
        cout<<"avformat_find_stream_info"<<endl;
    }
    cout<<"+++++++++info+++++++++"<<endl;
    av_dump_format(ifmt_ctx_v,0,input_filename_a,0);
    cout<<"+++++++++info+++++++++"<<endl;
    avformat_alloc_output_context2(&ofmt_ctx,NULL,NULL,out_filename);
    if(!ofmt_ctx)
    {
        cout<<"alloc context fail"<<endl;
    }
    ofmt = ofmt_ctx->oformat;//out struct;
    cout<<ifmt_ctx_v->nb_streams<<endl;
    for(int i=0;i < ifmt_ctx_v->nb_streams;i++)
    {
        AVStream *in_stream = ifmt_ctx_v->streams[i];
        AVStream *out_stream = avformat_new_stream(ofmt_ctx,in_stream->codec->codec);//codec info
        videoindex_v = i;
        if(!out_stream)
            cout<<"out_stream"<<endl;
        videoindex_out = out_stream->index;
        if(avcodec_copy_context(out_stream->codec,in_stream->codec)<0)//copy par;
            cout<<"copy fail"<<endl;
         out_stream->codec->codec_tag = 0;
        if(ofmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
        {
            out_stream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;
        }
    }
    cout<<"+++++++++info+++++++++"<<endl;
    av_dump_format(ofmt_ctx,0,out_filename,1);
    cout<<"+++++++++info+++++++++"<<endl;
    if(!(ofmt_ctx->flags & AVFMT_NOFILE))
    {
        if((avio_open(&ofmt_ctx->pb,out_filename,AVIO_FLAG_WRITE)) < 0)
            cout<<"open dst_file fail"<<endl;
    }
    if(avformat_write_header(ofmt_ctx,NULL) < 0)
    {
        cout<<"write header fail"<<endl;
    }










    //AVBitStreamFilterContext *h264bsfc = av_bitstream_filter_init("h264_mp4toannexb");
    while(1)
    {
        AVFormatContext *ifmt_ctx;
        int stream_index = 0;
        AVStream *in_stream,*out_stream;
        ifmt_ctx = ifmt_ctx_v;
        stream_index = videoindex_out;
        if(av_read_frame(ifmt_ctx,&pkt) >= 0)
        {
            {
                in_stream = ifmt_ctx->streams[pkt.stream_index];
                out_stream = ofmt_ctx->streams[stream_index];
                cout<<"stream_index "<<stream_index<<" "<<"pktstreamindex  "<<" "<<pkt.stream_index<<"videoindex  "<<" "<<videoindex_v<<endl;
                if(pkt.stream_index==videoindex_v)
                {
                    if(pkt.pts == AV_NOPTS_VALUE)
                    {
                        cout<<"frame_index"<<frame_index<<endl;
                        AVRational time_base1 = in_stream->time_base;
                        int64_t calc_duration = (double)AV_TIME_BASE/av_q2d(in_stream->r_frame_rate);

                        pkt.pts=(double)(frame_index * calc_duration)/(double)(av_q2d(time_base1)*AV_TIME_BASE);
                        cout<<"pts"<<pkt.pts<<endl;
                        pkt.dts = pkt.pts;
                        pkt.duration = (double)calc_duration/(double)(av_q2d(time_base1)*AV_TIME_BASE);
                        frame_index++;
                    }
                    cur_pts_v=pkt.pts;
                    //break;
                }
            }//while(av_read_frame(ifmt_ctx,&pkt) >=0);

        }
        //AVPacket new_pkt = pkt;
        if(pkt.size>0)
        {
        //av_bitstream_filter_filter(h264bsfc,in_stream->codec,NULL,&pkt.data,&pkt.size,pkt.data,pkt.size,0);//the function error

        //av_free_packet(&pkt);
        pkt.pts = av_rescale_q_rnd(pkt.pts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
//this have error
        pkt.dts = av_rescale_q_rnd(pkt.dts,in_stream->time_base,out_stream->time_base,(AVRounding)(AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX));
        pkt.duration = av_rescale_q(pkt.duration,in_stream->time_base,out_stream->time_base);
        pkt.pos = -1;
        pkt.stream_index=stream_index;
        cout<<"write a pack size is  "<<pkt.size<<"  pts  "<<pkt.pts<<endl;

        //pkt.data=new_pkt.data;
        //pkt.size=new_pkt.size;
        if(av_interleaved_write_frame(ofmt_ctx,&pkt) < 0)
        {
            printf("muxing fail");
            break;
        }
        av_free_packet(&pkt);
    }
        else
        {
            break;
        }
    }


    //write wei

    av_write_trailer(ofmt_ctx);
   // av_bitstream_filter_close(h264bsfc);
    avformat_close_input(&ifmt_ctx_v);
    avformat_free_context(ofmt_ctx);
    */
