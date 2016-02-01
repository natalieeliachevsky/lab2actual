#include "itkAddPixelAccessor.h"
#include "itkImage.h"
#include "itkImageAdaptor.h"
#include "itkImageDuplicator.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkImageRegionIterator.h"
#include "itkJPEGImageIOFactory.h"
#include "QuickView.h"


int main(int, char **)
{
    char inputFile[] = "C:/Users/Computron/Documents/GitHub/lab2actual/lab2actual/Lab2.jpg";
    char invertedFile[] = "C:/Users/Computron/Documents/GitHub/lab2actual/lab2actual/Lab2-inverted.jpg";
    char brightnessFile[] = "C:/Users/Computron/Documents/GitHub/lab2actual/lab2actual/Lab2-bright.jpg";
    char contrastFile[] = "C:/Users/Computron/Documents/GitHub/lab2actual/lab2actual/Lab2-contrast.jpg";
    unsigned int maximum = 255;
    unsigned int originalValue;
    unsigned int brightnessValue;
    unsigned int contrastValue;


    typedef itk::Image<unsigned char, 2> ImageType;
    typedef itk::ImageFileReader<ImageType> ReaderType;
    typedef itk::ImageDuplicator< ImageType > DuplicatorType;
    typedef  itk::ImageFileWriter< ImageType  > WriterType;

    // register jpeg
    itk::JPEGImageIOFactory::RegisterOneFactory();


    ReaderType::Pointer reader = ReaderType::New();
    ImageType::Pointer image = ImageType::New();
    ImageType::Pointer invertedImage = ImageType::New();
    ImageType::Pointer brightImage = ImageType::New();
    ImageType::Pointer contrastImage = ImageType::New();
    DuplicatorType::Pointer duplicator = DuplicatorType::New();
    WriterType::Pointer writer = WriterType::New();
    ImageType::IndexType index;


    //read file
    reader->SetFileName(inputFile);
    reader->Update();

    image = reader->GetOutput();

    /* copy image to intervtedImage*/
    duplicator->SetInputImage(image);
    duplicator->Update();

    invertedImage = duplicator->GetOutput();

    duplicator = DuplicatorType::New();
    duplicator->SetInputImage(image);
    duplicator->Update();

    brightImage = duplicator->GetOutput();

    duplicator = DuplicatorType::New();
    duplicator->SetInputImage(image);
    duplicator->Update();

    contrastImage = duplicator->GetOutput();


    ImageType::RegionType region = invertedImage->GetLargestPossibleRegion();
    ImageType::SizeType size = region.GetSize();


    for (unsigned int i = 0; i < size[0]; i++)
    {
        for (unsigned int j = 0; j < size[1]; j++)
        {
            index[0] = i;
            index[1] = j;

            originalValue = image->GetPixel(index);

            if (originalValue > maximum)
            {
                brightnessValue = 2;

            }

            brightnessValue = originalValue + 20;
            contrastValue = originalValue * 1.5;

            if (brightnessValue > maximum)
            {
                brightnessValue = maximum;
            }

            if (contrastValue > maximum)
            {
                contrastValue = maximum;
            }

            invertedImage->SetPixel(index, maximum - originalValue);
            brightImage->SetPixel(index, brightnessValue);
            contrastImage->SetPixel(index, contrastValue);
        }
    }

    invertedImage->Update();
    brightImage->Update();
    contrastImage->Update();


    /* write to files */
    writer->SetFileName(invertedFile);
    writer->SetInput(invertedImage);
    writer->Update();

    writer = WriterType::New();
    writer->SetFileName(brightnessFile);
    writer->SetInput(brightImage);
    writer->Update();

    writer = WriterType::New();
    writer->SetFileName(contrastFile);
    writer->SetInput(contrastImage);
    writer->Update();


    return EXIT_SUCCESS;
}
