/* Yep, we'll do this, allows to test static functions as well */
#define IN_TEST /* To remove the main from common.c */
#include "implem_seq.c"
#include "common.c"

#define RUN_TEST(test) \
do { \
        if (test() != 0) { \
                nbFailed++; \
        } \
} while (0)



int test_convolution_3_by_3(kernel_t kernel, struct image *pImg,
                            int16_t expectedValue, const char *testDesc)
{
        int16_t outPx;
        printf("It should %s... ", testDesc);
        convolution_3_by_3(pImg, kernel, 1, 1, &outPx);

        if (outPx == expectedValue) {
                printf("OK\n");
                return 0;
        } else {
                printf("FAILED: got %d instead of %d\n", outPx, expectedValue);
                return -1;
        }
}


static inline void make_3_3_img(struct image *pImg,
                               unsigned char v_0_0, unsigned char v_0_1, unsigned char v_0_2,
                               unsigned char v_1_0, unsigned char v_1_1, unsigned char v_1_2,
                               unsigned char v_2_0, unsigned char v_2_1, unsigned char v_2_2)
{
        pImg->type = GreyScale;
        pImg->width = 3;
        pImg->height = 3;
        pImg->data = calloc(9, sizeof(unsigned char));

        pImg->data[0] = v_0_0;
        pImg->data[1] = v_0_1;
        pImg->data[2] = v_0_2;

        pImg->data[3] = v_1_0;
        pImg->data[4] = v_1_1;
        pImg->data[5] = v_1_2;

        pImg->data[6] = v_2_0;
        pImg->data[7] = v_2_1;
        pImg->data[8] = v_2_2;
}


int test_conv_3_by_3_id()
{
        kernel_t kernel = {{0, 0, 0},
                           {0, 1, 0},
                           {0, 0, 0}};

        struct image mat = IMAGE_INITIALIZER;

        make_3_3_img(&mat, 2, 3, 4, 5, 6, 7, 8, 9, 10);

        return test_convolution_3_by_3(kernel, &mat, 6, "behave correctly with identity kernel");
}




int test_conv_3_by_3_null()
{
        kernel_t kernel = {{0, 0, 0},
                             {0, 0, 0},
                             {0, 0, 0}};

        struct image mat = IMAGE_INITIALIZER;

        make_3_3_img(&mat, 2, 3, 4, 5, 6, 7, 8, 9, 10);
        return test_convolution_3_by_3(kernel, &mat, 0, "behave correctly with null kernel");
}



int test_conv_3_by_3_ex1()
{
        kernel_t kernel;
        (void) initKernelY(kernel);
        
        struct image mat = IMAGE_INITIALIZER;

        make_3_3_img(&mat, 2, 3, 4, 5, 6, 7, 8, 9, 10);
        return test_convolution_3_by_3(kernel, &mat, -24, "behave correctly with Y kernel");
}



int test_conv_3_by_3_uniformeY()
{
        kernel_t kernel;
        (void) initKernelY(kernel);
        
        struct image mat = IMAGE_INITIALIZER;

        make_3_3_img(&mat, 100, 100, 100, 100, 100, 100, 100, 100, 100);
        return test_convolution_3_by_3(kernel, &mat, 0, "behave correctly with Y kernel on uniform area");
}



int test_conv_3_by_3_uniformeX()
{
        kernel_t kernel;
        (void) initKernelX(kernel);
        
        struct image mat = IMAGE_INITIALIZER;

        make_3_3_img(&mat, 100, 100, 100, 100, 100, 100, 100, 100, 100);
        return test_convolution_3_by_3(kernel, &mat, 0, "behave correctly with X kernel on uniform area");
}



int main(void)
{
        int nbFailed = 0;

        RUN_TEST(test_conv_3_by_3_id);
        RUN_TEST(test_conv_3_by_3_null);
        RUN_TEST(test_conv_3_by_3_ex1);
        RUN_TEST(test_conv_3_by_3_uniformeX);
        RUN_TEST(test_conv_3_by_3_uniformeY);


        return nbFailed;
}
