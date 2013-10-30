#include "TrackFace.h"
#include "ui_trackface.h"

TrackFace::TrackFace(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TrackFace)
{
    /* Set File Source Variables */

    fn_path="/Users/dgyHome/Documents/QT/TrackFace/";
    fn_images=fn_path+"resources/train_image.in";
    fn_haar=fn_path+"resources/haarcascade_frontalface_default.xml";
    fn_features=fn_path+"resources/features.in";
    fn_namedb=fn_path+"resources/namedb.in";

    im_width=150;
    im_height=150;

    /* Open DataBase */

    try
    {
        iofunctions.read_images(fn_images,fn_path,images,labels);
        iofunctions.read_name(fn_namedb,names);
    }
    catch(cv::Exception & e)
    {
        cout << "Error" << endl;
        exit(1);
    }

    /* Train/Load Features */
    if (!labels.empty() && labels[labels.size()-1]!=0)
    {
        if (QDir(fn_features.c_str()).exists())
            model->load(fn_features);
        else training();
    }

    haar_cascade.load(fn_haar);

    /* Load GUI */

    ui->setupUi(this);
}

TrackFace::~TrackFace()
{
    delete ui;
}

void TrackFace::on_grabPhoto_clicked()
{
    // new window to collect information
    /*

    transmit data between form is tricky.
    grabForm.show();
    string message=grabForm.getMsg();

    cout << message << endl;
    */

    string name=ui->grabName->text().toStdString();
    cout << name << endl;

    string namepath=iofunctions.addName(name, fn_namedb, fn_path);
    int counter=1;

    int label=0;
    if (!labels.empty()) label=labels[labels.size()-1]+1;

    // Face tracking
    TrackFace::capture.open(0);

    cv::namedWindow("Grab Face", cv::WINDOW_AUTOSIZE);
    moveWindow("Grab Face", 300, 300);

    while(true)
    {
        cv::Mat frame, buffer;
        if (!capture.isOpened()) break;

        capture >> buffer;
        cv::resize(buffer, frame,Size(buffer.cols/2,buffer.rows/2),0,0,INTER_LINEAR);


        vector<cv::Rect_<int> > faces=haar_faces(frame);

        if (faces.size()>0)
        {
            size_t n=findMaxFace(faces);

            Mat resizedFace=resizeFace(frame(faces[n]), im_width, im_height);

            while (counter<=20)
            {
                string imgPath=namepath+name+"_"+(char)(counter+'A'-1)+".jpg";
                cv::imwrite(imgPath,resizedFace);
                iofunctions.addToTrain(fn_images,"resources/"+name+"/"+name+"_"+(char)(counter+'A'-1)+".jpg", label);
                counter++;
            }

            drawFace(frame, faces[n], name);
        }

        cv::imshow("Grab Face", frame);

        while (cv::waitKey(5)==27)
        {
            capture.release();
            cv::destroyWindow("Grab Face");
        }
    }
}

void TrackFace::on_training_clicked()
{
    training();
}

void TrackFace::on_recognition_clicked()
{
    TrackFace::capture.open(0);

    cv::namedWindow("Track Face", cv::WINDOW_AUTOSIZE);
    moveWindow("Track Face", 300, 300);

    while (true)
    {
        cv::Mat frame, buffer;
        if (!capture.isOpened()) break;

        capture >> buffer;
        cv::resize(buffer, frame,Size(buffer.cols/2,buffer.rows/2),0,0,INTER_LINEAR);

        vector<Rect_<int> > faces=haar_faces(frame);

        for (size_t i=0;i<faces.size();i++)
        {
            cv::Mat face_resized=resizeRecognitionFace(frame, faces[i]);

            int prediction=model->predict(face_resized);

            string box_text=format("Prediction = %s", names[prediction].c_str());

            drawFace(frame, faces[i], box_text);
        }

        cv::imshow("Track Face", frame);
        while (cv::waitKey(5)==27)
        {
            capture.release();
            cv::destroyWindow("Track Face");
        }
    }
}


// Utilities

void TrackFace::training()
{
    model=createFisherFaceRecognizer();

    model->train(images, labels);

    model->save(fn_features);
}

vector<Rect_<int> > TrackFace::haar_faces(cv::Mat frame)
{
    cv::Mat gray;
    cv::cvtColor(frame, gray, CV_BGR2GRAY);

    vector<Rect_<int> > faces;

    haar_cascade.detectMultiScale(gray, faces);

    return faces;
}

void TrackFace::drawFace(cv::Mat & frame, cv::Rect & face_n, string box_text)
{
    rectangle(frame, face_n, CV_RGB(0,255,0),1);
    int pos_x=std::max(face_n.tl().x-10, 0);
    int pos_y=std::max(face_n.tl().y-10, 0);
    putText(frame, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0,255,0),2.0);
}

size_t TrackFace::findMaxFace(vector<cv::Rect_<int> > faces)
{
    size_t n=0;
    int max=-1;
    for (size_t i=0;i<faces.size();i++)
    {
        if (max<faces[i].height*faces[i].width)
        {
            max=faces[i].height*faces[i].width;
            n=i;
        }
    }

    return n;
}

cv::Mat TrackFace::resizeRecognitionFace(cv::Mat frame, cv::Rect face_n)
{
    cv::Mat face=frame(face_n);
    cv::Mat grayFace;
    cv::cvtColor(face, grayFace, CV_BGR2GRAY);

    cv::Mat resizedFace;
    cv::resize(grayFace, resizedFace, Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);

    return resizedFace;
}

cv::Mat TrackFace::resizeFace(cv::Mat face, int width, int height)
{
    cv::Mat resizedFace;
    cv::resize(face, resizedFace, cv::Size(width, height), 1.0, 1.0, INTER_LINEAR);

    return resizedFace;
}
