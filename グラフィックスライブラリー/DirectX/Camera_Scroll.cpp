//�Q�[���G���W���Ɏ�������	Camera�̂��߂̎����R�[�h

//scroll

//Note: �J���� �� �w�i �摜 �� �t ���� �� �����A �܂� �J���� 
//�� �� �� ���� �� �w�i �� �E ���� �� ����A
//�J���� �� �E ���� �� ���� �� �w�i �� �� ���� �� �����A

#define PICTURE_WIDTH�@1600				// �w�i��
#define VIEW_WIDTH  500
#define CAMERA_VEL	10.0f				// �J��������

float fCamera_x; //�J�������f�����S���W
float fBack_x; //�w�i�摜�̍��[��x���W


int InitBack( void )							// �ŏ��ɂP�񂾂��Ă΂��
{
	fCamera_x = VIEW_WIDTH / 2.0f;				// �J�����̏����ʒu
	fBack_x = VIEW_WIDTH / 2.0f - fCamera_x;	// �w�i�̏����ʒu " - fCamera_ x�h

	return 0;
}


int MoveBack( void )							// ���t���[���Ă΂��
{
	// ���L�[��������Ă���΍���
	if ( GetAsyncKeyState( VK_LEFT ) )
	{
		fCamera_x -= CAMERA_VEL;
		if ( fCamera_x < VIEW_WIDTH / 2.0f ) 
		{
			//�J���������͂��ɍs���܂�
			fCamera_x = VIEW_WIDTH / 2.0f;
		}
	}
	// �E�L�[��������Ă���ΉE��
	if ( GetAsyncKeyState( VK_RIGHT ) )
	{
		fCamera_x += CAMERA_VEL;
		if ( fCamera_x > ( float )( PICTURE_WIDTH - VIEW_WIDTH / 2.0f ) )
		{
			//�J�������E�͂��ɍs���܂�
			fCamera_x = ( float )( PICTURE_WIDTH - VIEW_WIDTH / 2.0f );
		}
	}

	fBack_x = VIEW_WIDTH / 2.0f - fCamera_x;	// �w�i�̈ʒu

	return 0;
}

// �w�i�̑��d�X�N���[��
// ���̊�������
//------------------------------------------------------------

//note:�w�i�̉������������قǁA�X�N���[���̑��x�͒ቺ����
//���L�̏ꍇ�APICTURE_WIDTH3����Ԓx���Ȃ�悤�Ƀv���O��������
#define PICTURE_WIDTH1		1600				// �w�i1��
#define PICTURE_WIDTH2		1280				// �w�i2��
#define PICTURE_WIDTH3		873					// �w�i3
float		fBack_x1, fBack_x2, fBack_x3;


int InitBack( void )							// �ŏ��ɂP�񂾂��Ă΂��
{
	fCamera_x = VIEW_WIDTH / 2.0f;				// �J�����̏����ʒu�@
	fBack_x1 = 0.0f;							// �őO�ʔw�i��
	fBack_x2 = 0.0f;// �Q�߂̂͂�����
	fBack_x3 = 0.0f;// �ŉ��̔w�i

	return 0;
}


int MoveBack( void )							// ���t���[���Ă΂��
{
	// ���L�[��������Ă���΍���
	if ( GetAsyncKeyState( VK_LEFT ) ) 
	{
		fCamera_x -= CAMERA_VEL;
		if ( fCamera_x < VIEW_WIDTH / 2.0f ) {
			fCamera_x = VIEW_WIDTH / 2.0f;
		}
	}
	// �E�L�[��������Ă���ΉE��
	if ( GetAsyncKeyState( VK_RIGHT ) ) {
		fCamera_x += CAMERA_VEL;
		if ( fCamera_x > ( float )( PICTURE_WIDTH1 - VIEW_WIDTH / 2.0f ) )
		{
			fCamera_x = ( float )( PICTURE_WIDTH1 - VIEW_WIDTH / 2.0f );
		}
	}
	fBack_x1 = VIEW_WIDTH / 2.0f - fCamera_x;
	//�X�N���[���\���̔䗦�ő��x�����߂�
	fBack_x2 = ( float )( PICTURE_WIDTH2 - VIEW_WIDTH ) / ( PICTURE_WIDTH1 - VIEW_WIDTH ) * fBack_x1; 
	fBack_x3 = ( float )( PICTURE_WIDTH3 - VIEW_WIDTH ) / ( PICTURE_WIDTH1 - VIEW_WIDTH ) * fBack_x1;

	return 0;
}