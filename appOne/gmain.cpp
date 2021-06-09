#include"libOne.h"
//���_�ʒu�̍\����
struct POS {  //���_�̍\����
    float x, y, z;
};
//�Q�[�����C��
void gmain() {
    window(1000, 1000);
    //���_�̐�
    int numCorners = 10; //�O���猩�Ĕ��p�`
    int numRings = 4;//10�p�`�𕡐��p�ӂ��邽�߂̃����O�X
    int numVertices = numCorners * numRings;
    //�i���R�[�i�[�Y�ƃi�������O�X���|�������_���i�����@�[�e�B�V�[�Y���_��
    int Co = numCorners;
    float deg = 360.0f / numCorners;//x,y�p�̊p�x
    float deg2 = 360.0f / 6;//x,z�p�̊p�x
    angleMode(DEGREES);

    struct POS* op = new POS[numVertices]; //���I�m��
    //op���i�����@�[�e�B�V�[�Y�������p�ӂ����@op�i���@�[�e�B�V�[�Y
    //���p�`�̒��_��sin�Acos���g���ĕ\�����Ă�
    for (int j = 0;j <numRings;j++) {
        float r = sin(deg2 * j);
        float z = cos(deg2 * j)*0.3;
        for (int i = 0;i < numCorners;i++){
            float radius = 0.5f + 0.5f * (i % 2); 
            //i�͂O����V�܂ł����ω����Ȃ����̕��܂ŕω�������
            //�P���z����Q�����I�g�p������@
            int k = j * numCorners + i;        
            op[k].x = sin(deg * i)*radius *r;
            op[k].y = -cos(deg * i)*radius *r;
            op[k].z = z;//1.0f - 2.0f / (numRings - 1) * j;
            //���s�̂��̒l�A������v�Z���čs����0.5,1,0,-0.5,-1
        }
    }
    struct POS* p = new POS[numVertices]; //p���i�����@�[�e�B�V�[�Y�������p�ӂ���


    int state = 0;
    int flug = 0;
    while (notQuit) {
        clear(0);
        if (flug == 0) {
            deg += 1;
        }
        float s = sin(deg);
        float c = cos(deg);
        if (deg > 360) {
            deg = 0;
            ++state %= 2;
        }
        if (isTrigger(KEY_SPACE)) {
            ++flug;
            flug %= 2;
        }
        for (int i = 0;i < numVertices;i++) {
            if (state == 0) {
                p[i].x = op[i].x * c + op[i].z * -s;
                p[i].y = op[i].y;
                p[i].z = op[i].x * s + op[i].z * c;
            }
            //�ŏ�������W��1�w�肵�Ă�����
            //���̍��W��sin�Ecos���g���ĉ�]�����Ă���
            //�K���ɑł������W����]�����邱�Ƃ��ł���
            //p[i].x = op[i].x;
            else if (state == 1) {
                p[i].y = op[i].y * c + op[i].z * -s;
                p[i].x = op[i].x;
                p[i].z = op[i].y * s + op[i].z * c;
            }
            //p[i].z = op[i].z + s; //�y�i���s�j�̉^�����傫���ق�X,Y�̍��W���������Ȃ�
            p[i].z += 5;

            p[i].x /= p[i].z;
            p[i].y /= p[i].z;
        }
        mathAxis(0.5);
        stroke(255, 255, 0);
        for (int i = 0;i < numVertices;i++) {
            int j = i + 1;
            if (j % numCorners == 0) { j -= numCorners; }
            strokeWeight(6);
            mathPoint(p[i].x, p[i].y);
            strokeWeight(2);
            mathLine(p[i].x, p[i].y, p[j].x, p[j].y);

            if (j < numVertices - numCorners) {
                j = i + numCorners;
                mathLine(p[i].x, p[i].y, p[j].x, p[j].y);
            }
        }
    }
    delete[]p;
    delete[]op;
}

/*
#include"libOne.h"
//���_�ʒu�̍\����
struct POS {  //���_�̍\����
    float x, y, z;
};
//�Q�[�����C��
void gmain() {
    window(1000, 1000);
    //���_�̐�
    int numCorners = 8; //�O���猩�Ĕ��p�`
    int numRings = numCorners / 2 + 1;//��X���p�`�𕡐��p�ӂ��邽�߂̃����O�X
    int numVertices = numCorners * numRings;
    //�i���R�[�i�[�Y�ƃi�������O�X���|�������_���i�����@�[�e�B�V�[�Y���_��    

    float deg = 360.0f / numCorners;
    angleMode(DEGREES);

    struct POS* op = new POS[numVertices]; //���I�m��
    //op���i�����@�[�e�B�V�[�Y�������p�ӂ����@op�i���@�[�e�B�V�[�Y
    //���p�`�̒��_��sin�Acos���g���ĕ\�����Ă�
    for (int j = 0;j < numRings;j++) {
        float r = sin(deg * j);
        float z = cos(deg * j);
        for (int i = 0;i < numCorners;i++) {
            //i�͂O����V�܂ł����ω����Ȃ����̕��܂ŕω�������
            //�P���z����Q�����I�g�p������@
            int k = j * numCorners + i;
            op[k].x = sin(deg * i) * r;
            op[k].y = cos(deg * i) * r;
            op[k].z = z;//1.0f - 2.0f / (numRings-1) * j;
            //���s�̂��̒l�A������v�Z���čs����0.5,1,0,-0.5,-1
        }
    }
    struct POS* p = new POS[numVertices]; //p���i�����@�[�e�B�V�[�Y�������p�ӂ���


    int state = 0;
    int flug = 0;
    while (notQuit) {
        clear(0);
        if (flug == 0) {
            deg += 1;
        }
        float s = sin(deg);
        float c = cos(deg);
        if (deg > 360) {
            deg = 0;
            ++state %= 2;
        }
        if (isTrigger(KEY_SPACE)) {
            ++flug;
            flug %= 2;
        }
        for (int i = 0;i < numVertices;i++) {
            if (state == 0) {
                p[i].x = op[i].x * c + op[i].z * -s;
                p[i].y = op[i].y;
                p[i].z = op[i].x * s + op[i].z * c;
            }
            //�ŏ�������W��1�w�肵�Ă�����
            //���̍��W��sin�Ecos���g���ĉ�]�����Ă���
            //�K���ɑł������W����]�����邱�Ƃ��ł���
            //p[i].x = op[i].x;
            else if (state == 1) {
                p[i].y = op[i].y * c + op[i].z * -s;
                p[i].x = op[i].x;
                p[i].z = op[i].y * s + op[i].z * c;
            }
            //p[i].z = op[i].z + s; //�y�i���s�j�̉^�����傫���ق�X,Y�̍��W���������Ȃ�
            p[i].z += 5;

            p[i].x /= p[i].z;
            p[i].y /= p[i].z;
        }
        mathAxis(0.5);
        stroke(200, 255, 255);
        for (int i = 0;i < numVertices;i++) {
            int j = i + 1;
            if (j % numCorners == 0) { j -= numCorners; }
            strokeWeight(6);
            mathPoint(p[i].x, p[i].y);
            strokeWeight(2);
            mathLine(p[i].x, p[i].y, p[j].x, p[j].y);

            if (j < numVertices - numCorners) {
                j = i + numCorners;
                mathLine(p[i].x, p[i].y, p[j].x, p[j].y);
            }
        }
    }
    delete[]p;
    delete[]op;
}
*/
/*
#include"libOne.h"
//���_�ʒu�̍\����
struct POS {
    float x, y, z;
};
void setSphere(struct POS* op, int numCorners, int numRings) {
    float deg = 360.0f / numCorners;
    angleMode(DEGREES);
    for (int j = 0; j < numRings; j++) {
        float r = sin(deg * j);
        float z = cos(deg * j);
        for (int i = 0; i < numCorners; i++) {
            int k = j * numCorners + i;
            op[k].x = sin(deg * i) * r;
            op[k].y = cos(deg * i) * r;
            op[k].z = z;
        }
    }
}
void setCylinder(struct POS* op, int numCorners, int numRings) {
    float deg = 360.0f / numCorners;
    angleMode(DEGREES);
    for (int j = 0; j < numRings; j++) {
        for (int i = 0; i < numCorners; i++) {
            int k = j * numCorners + i;
            op[k].x = sin(deg * i);
            op[k].y = cos(deg * i);
            op[k].z = 1.0f - 2.0f / (numRings - 1) * j;
        }
    }
}
//�Q�[�����C��
void gmain() {
    window(1000, 1000, full);
    //���_�̐�
    int numCorners = 32;
    int numRings = numCorners / 2 + 1;
    int numVertices = numCorners * numRings;
    //���̒��_�ʒu�i���[�v�����ێ�����Ă���B�ω����Ȃ��j
    struct POS* op = new POS[numVertices];
    float deg = 360.0f / numCorners;
    angleMode(DEGREES);
    setSphere(op, numCorners, numRings);
    //�ύX��̒��_�ʒu�̓��ꕨ�i���[�v���邽�тɕω�����j
    struct POS* p = new POS[numVertices];
    //���̒��_�ʒu����]������p�x
    deg = 0;
    //����state��0�̎�Y���A1�̎�X����]����
    int state = 0;
    int sw = 1;
    //���C�����[�v
    while (notQuit) {
        //���_�ʒu�ύX
        if (isTrigger(KEY_SPACE)) {
            sw = 1 - sw;
            if (sw == 0)setCylinder(op, numCorners, numRings);
            else setSphere(op, numCorners, numRings);
        }
        //���炩����sin,cos���v�Z���Ă���
        float s = sin(deg);
        float c = cos(deg);
        deg++;
        //state�̕ύX
        if (deg > 360) {
            deg = 0;
            ++state %= 2;
        }
        //�z��op�̍��W��ϊ����Ĕz��p�ɏ�������
        // ( �z��op�̈ʒu�͕ς��Ȃ� )
        for (int i = 0; i < numVertices; i++) {
            //��]
            if (state == 0) {
                p[i].x = op[i].x * c + op[i].z * -s;
                p[i].y = op[i].y;
                p[i].z = op[i].x * s + op[i].z * c;
            }
            else {
                p[i].x = op[i].x;
                p[i].y = op[i].y * c + op[i].z * -s;
                p[i].z = op[i].y * s + op[i].z * c;
            }
            //���Ɉړ�
            p[i].z += 5;
            //�����̍��W������������
            p[i].x /= p[i].z;
            p[i].y /= p[i].z;
        }
        //���_�ʒu����Ō��ы��̂ɂ���
        clear(0);
        mathAxis(0.5);//�N���A�F�Ɠ����Ŏ��͌����Ȃ����K�v�Ȗ���
        stroke(160, 200, 255);
        for (int i = 0; i < numVertices; i++) {
            //���_
            //strokeWeight(6);
            //mathPoint(p[i].x, p[i].y);
            //�����O�̒��_����Ō���
            int j = i + 1;
            if (j % numCorners == 0)j -= numCorners;
            strokeWeight(2);
            mathLine(p[i].x, p[i].y, p[j].x, p[j].y);
            //�O��̒��_����Ō���
            if (i < numVertices - numCorners) {
                j = i + numCorners;
                mathLine(p[i].x, p[i].y, p[j].x, p[j].y);
            }
        }
    }
    delete[]op;
    delete[]p;
}
*/