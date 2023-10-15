//���_
//�����x�̍팸 > �ˑ�����.cpp�Ɉړ����A�����v�f�����ׂď����ł���
//�R���p�C�����Ԃ̍����� > API�̃C���N���[�h�K�w���팸�ł���
//�o�C�i���݊����̌��� > pimpl�I�u�W�F�N�g�̓V���O���|�C���^�P�̂� > �I�u�W�F�N�g�̃o�C�i���\����ύX�����ɁA�����ɑ傫�ȕύX�������邱�Ƃ��ł���
//���C�W�[������ > mimpl�N���X�͕K�v�ɉ����č쐬�ł��� > �l�b�g���[�N�ڑ��Ȃǂ̐����̂��郊�\�[�X��R�X�g�̍������\�[�X���N���X�������Ă�ꍇ�ɖ𗧂�

//���_
//�쐬�����I�u�W�F�N�g���Ƃɒǉ��̎����I�u�W�F�N�g�������� > �����ĉ������Ȃ��Ă͂����Ȃ�
//�R���p�C����const���\�b�h���̃����o�ϐ��̕ύX���L���b�`���Ȃ��Ȃ� (�����o�ϐ������͂�ʂ̃I�u�W�F�N�g�ɑ��݂��邩��)


#include <memory>
#include <string>

class Person
{
 public:
   // ...
   Person();
   ~Person();

   Person( Person const& other );
   Person& operator=( Person const& other );

   Person( Person&& other );
   Person& operator=( Person&& other );

   int year_of_birth() const;
   // ... Many more access functions

 private:
   struct Impl;
   std::unique_ptr<Impl> const pimpl_;
};



struct Person::Impl
{
   std::string forename;
   std::string surname;
   std::string address;
   std::string city;
   std::string country;
   std::string zip;
   int year_of_birth;
   // ... Potentially many more data members
};


Person::Person()
   : pimpl_{ std::make_unique<Impl>() }
{}

Person::~Person() = default;

Person::Person( Person const& other )
   : pimpl_{ std::make_unique<Impl>(*other.pimpl_) }
{}

Person& Person::operator=( Person const& other )
{
   *pimpl_ = *other.pimpl_;
   return *this;
}

Person::Person( Person&& other )
   : pimpl_{ std::make_unique<Impl>(std::move(*other.pimpl_)) }
{}

Person& Person::operator=( Person&& other )
{
   *pimpl_ = std::move(*other.pimpl_);
   return *this;
}

int Person::year_of_birth() const
{
   return pimpl_->year_of_birth;
}


int main()
{
   Person p1{};

   return EXIT_SUCCESS;
}
