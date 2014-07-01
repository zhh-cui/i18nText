#include "include/i18nText.h"

int main(int argc, char **argv) {
    try {
        cv::Mat test(150, 400, CV_8UC3, CV_RGB(0, 255, 0));
        cv::namedWindow("test", CV_WINDOW_NORMAL);
        i18nText i18n;
        if (i18n.setFont("/usr/share/fonts/truetype/wqy/wqy-microhei.ttc")) {
          std::cout << "Load fonts successfully." << std::endl;
    
          const wchar_t *msg = L"汉字 iw0ol1 ニホンゴ";
          std::cout << "Put ";
          int num = i18n.putText(test, msg, cv::Point(25, 50), CV_RGB(0, 0, 255));
          std::cout << num << " chars." << std::endl;
    
          const wchar_t *msg2 = L"조선말／朝鮮말，한국어／韓國語";
          std::cout << "Put another ";
          num = i18n.putText(test, msg2, cv::Point(25, 100), CV_RGB(255, 0, 0));
          std::cout << num << " chars." << std::endl;
        }
    } catch (cv::Exception e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
