//#include <iostream>
//#include <algorithm>
//#include <windows.h>
//#include <deque>
//
//template <unsigned ALIGN>
//inline unsigned alignDown(unsigned value) {
//	return value&(0ul - ALIGN);
//}
//
//template <unsigned ALIGN>
//inline unsigned alignUp(unsigned value) {
//	return value + ALIGN - 1ul & (0ul - ALIGN);
//}
//
//inline unsigned getBitString(const unsigned char *bits,
//	unsigned num) {
//	return (bits[num / 8] >> (7ul - num % 8)) & 1ul;
//}
//
//template <unsigned BIT>
//inline unsigned maskBit() {
//	return (1ul << BIT) - 1ul;
//}
//
//#define MASK_BIT(bit) ((1ul<<(bit))-1ul)
//
////--------------------------------------------------------
//// класс описывающий узел
//__declspec(align(4)) class Node
//{
//public:
//	// get
//	// links
//	Node *getXlink(unsigned id) const
//	{
//		return reinterpret_cast<Node*>(linktag_[id] & ~1ul);
//	}
//	Node *getLlink() const
//	{
//		return getXlink(0);
//	}
//	Node *getRlink() const
//	{
//		return getXlink(1);
//	}
//	// tags
//	unsigned getXtag(unsigned id) const
//	{
//		return linktag_[id] & 1ul;
//	}
//	unsigned getLtag() const
//	{
//		return getXtag(0);
//	}
//	unsigned getRtag() const
//	{
//		return getXtag(1);
//	}
//	// skip
//	unsigned getSkip() const
//	{
//		return skip_;
//	}
//	// set
//	// links&tags
//	void setXlinktag(unsigned id, Node *link, unsigned tag)
//	{
//		linktag_[id] = reinterpret_cast<unsigned>(link) | tag;
//	}
//	void setLlinktag(Node *llink, unsigned tag)
//	{
//		setXlinktag(0, llink, tag);
//	}
//	void setRlinktag(Node *rlink, unsigned tag)
//	{
//		setXlinktag(1, rlink, tag);
//	}
//	// skip
//	void setSkip(unsigned skip)
//	{
//		skip_ = skip;
//	}
//	// init root
//	void initializeRoot()
//	{
//		// левый линк указывает на себя (корень)
//		setLlinktag(this, 1);
//	}
//private:
//	unsigned linktag_[2];
//	unsigned skip_;
//};
////--------------------------------------------------------
//// класс алгоритма P (см. Кнут, "Искусство программирования",
//// "Сортировка и поиск")
//class PatAlgorithm
//{
//public:
//	// инициализирующий конструктор
//	PatAlgorithm(Node *root)
//		: q_(root)
//		, p_(q_->getLlink())
//		, j_(p_->getSkip())
//		, qid_(0)
//		, qtag_(q_->getLtag())
//	{
//	}
//	// инициализация существуюшего объекта
//	void initialize(Node *root)
//	{
//		q_ = root; p_ = q_->getLlink();
//		j_ = p_->getSkip();
//		qid_ = 0; qtag_ = q_->getLtag();
//	}
//	// прогон алгоритма P
//	void run(const unsigned char *k, unsigned n)
//	{
//		if (qtag_ == 0) while (j_<n&&iterateByK(k));
//	}
//	// найти контекст по строке k числом символов n
//	// начало текстового буфера - text
//	bool findContext(Node *root, const unsigned char *k,
//		unsigned n, const unsigned char *text)
//	{
//		run(k, n * 8);
//		return std::equal(k, k + n, text + getText(root));
//	}
//	unsigned getText(Node *root) const
//	{
//		return p_ - root;
//	}
//protected:
//	// одна классическая итерация алгоритма P
//	bool iterate()
//	{
//		q_ = p_;
//		p_ = q_->getXlink(qid_);
//		qtag_ = q_->getXtag(qid_);
//		if (qtag_) return false;
//		j_ = p_->getSkip();
//		return true;
//	}
//	// итерация по ключу
//	bool iterateByK(const unsigned char *k)
//	{
//		qid_ = getBitString(k, j_);
//		return iterate();
//	}
//	Node *q_, *p_;
//	unsigned j_;
//	unsigned qid_, qtag_;
//};
////--------------------------------------------------------
//// класс прохода по дереву
//class PatIterator
//	: public PatAlgorithm
//{
//public:
//	// инициализирующий конструктор
//	PatIterator(Node *root)
//		: PatAlgorithm(root)
//		, lowBound_(0)
//	{
//	}
//	PatIterator(const PatIterator &pit)
//		: PatAlgorithm(pit)
//		, lowBound_(descent_.size())
//	{
//	}
//	// прогон алгоритма P влево (ограничение по битам)
//	void runLeft(unsigned n)
//	{
//		if (qtag_ == 0 && j_<n)
//		{
//			qid_ = 0;
//			do
//			{
//				descent_.push_back(p_);
//			} while (iterate() && j_<n);
//		}
//	}
//	// прогон алгоритма P влево (без ограничений)
//	void runLeft()
//	{
//		if (qtag_ == 0)
//		{
//			qid_ = 0;
//			do
//			{
//				descent_.push_back(p_);
//			} while (iterate());
//		}
//	}
//	// идти направо
//	bool goRight()
//	{
//		if (descent_.size()>lowBound_)
//		{
//			p_ = descent_.back();
//			descent_.pop_back();
//			j_ = p_->getSkip();
//			qid_ = 1;
//			iterate();
//			return true;
//		}
//		else
//			return false;
//	}
//	unsigned getJ(unsigned w) const
//	{
//		return qtag_ ? w * 8 : j_ + 1;
//	}
//protected:
//	// прогон алгоритма P с историей узлов Q
//	void run(const unsigned char *k, unsigned n)
//	{
//		if (qtag_ == 0) while (j_<n)
//		{
//			descent_.push_back(p_);
//			if (!iterateByK(k))
//				break;
//		}
//	}
//	static std::deque<Node*> descent_;
//	const unsigned lowBound_;
//};
////--------------------------------------------------------
//std::deque<Node*> PatIterator::descent_;
////--------------------------------------------------------
//// функция посимвольного сравнения строк
//inline unsigned compareStringByte(const unsigned char *a,
//	const unsigned char *b)
//{
//	const unsigned char *startA = a;
//	for (; *a == *b; ++a, ++b);
//	return a - startA;
//}
////--------------------------------------------------------
//// сравнение строк
//inline unsigned compareString(const unsigned char *a,
//	const unsigned char *b)
//{
//	const unsigned
//		offA = reinterpret_cast<unsigned>(a) % 4,
//		offB = reinterpret_cast<unsigned>(b) % 4;
//	const unsigned
//		*alA = reinterpret_cast<const unsigned*>
//		(alignDown<4>(reinterpret_cast<unsigned>(a))),
//		*alB = reinterpret_cast<const unsigned*>
//		(alignDown<4>(reinterpret_cast<unsigned>(b)));
//	unsigned id = 0;
//	// если фазы совпадают
//	if (offA == offB)
//	{
//		if (offA)
//		{
//			for (; offA + id != 4; ++id)
//			{
//				if (*a++ != *b++)
//					return id;
//			}
//			++alA; ++alB;
//		}
//		for (; *alA++ == *alB++; id += 4);
//		a += alignDown<4>(id); b += alignDown<4>(id);
//		for (; *a++ == *b++; ++id);
//	}
//	else
//		for (a += id, b += id; *a++ == *b++; ++id);
//	return id;
//}
////--------------------------------------------------------
//class PatAddNodeBase
//	: protected PatAlgorithm
//{
//public:
//	static void initAdd()
//	{
//		lastId_ = lastMatch_ = 0;
//	}
//protected:
//	PatAddNodeBase();
//	PatAddNodeBase(PatAddNodeBase&);
//	PatAddNodeBase(Node *root)
//		: PatAlgorithm(root)
//	{
//	}
//	unsigned matchFunc(unsigned id, const unsigned char *k,
//		const unsigned char *key)
//	{
//		unsigned offs = id - lastId_;
//		lastId_ = id;
//		return lastMatch_ =
//			lastMatch_>offs
//			? offs = lastMatch_ - offs, offs
//			+ compareStringByte(k + offs, key + offs)
//			: compareStringByte(k, key);
//	}
//	static unsigned lastId_, lastMatch_;
//};
////--------------------------------------------------------
//unsigned PatAddNodeBase::lastId_ = 0;
//unsigned PatAddNodeBase::lastMatch_ = 0;
////--------------------------------------------------------
//// класс добавления нового узла в дерево
//// (с проверкой на конец)
//class PatAddNode
//	: private PatAddNodeBase
//{
//public:
//	// конструктор, выполняющий добавление немедленно
//	PatAddNode(unsigned L, Node *root,
//		const unsigned char *text, unsigned id)
//		: PatAddNodeBase(root)
//	{
//		const unsigned char *k = text + id;
//		run(k, L * 8);
//		const unsigned char *key = text + getText(root);
//		// находим l (номер первого несовпадающего бита)
//		// сравниваем k и key
//		unsigned l = matchFunc(id, k, key);
//		if (isNewNode_ = id + l + 1 != 2 * L)
//		{
//			// берем новый узел
//			// если найдены отличия
//			// на уровне битов
//			unsigned mismatch = k[l] ^ key[l];
//			for (l *= 8; (mismatch & 0x80) == 0; ++l, mismatch <<= 1);
//			// значение несовпадающего бита в k
//			const unsigned b = getBitString(k, l);
//			// повтор алгоритма P для первых l битов
//			if (j_ >= l)
//			{
//				initialize(root);
//				run(k, l);
//			}
//			//
//			Node *r = root + id;
//			//
//			q_->setXlinktag(qid_, r, 0);
//			//
//			r->setXlinktag(b, r, 1);
//			r->setXlinktag(1ul ^ b, p_, qtag_);
//			//
//			r->setSkip(l);
//		}
//	}
//	// функция добавления
//	// возвращает true, если узел был добавлен
//	bool isNewNode() const
//	{
//		return isNewNode_;
//	}
//private:
//	bool isNewNode_;
//};
////--------------------------------------------------------
//// класс добавления нового узла в дерево
//// (без проверки на конец)
//class PatAddNodeFast
//	: private PatAddNodeBase
//{
//public:
//	// конструктор, выполняющий добавление немедленно
//	PatAddNodeFast(unsigned L, Node *root,
//		const unsigned char *text, unsigned id)
//		: PatAddNodeBase(root)
//	{
//		const unsigned char *k = text + id;
//		run(k, L * 8);
//		const unsigned char *key = text + getText(root);
//		// находим l (номер первого несовпадающего бита)
//		// сравниваем k и key
//		unsigned l = matchFunc(id, k, key);
//		// берем новый узел
//		// если найдены отличия
//		// на уровне битов
//		unsigned mismatch = k[l] ^ key[l];
//		for (l *= 8; (mismatch & 0x80) == 0; ++l, mismatch <<= 1);
//		// значение несовпадающего бита в k
//		const unsigned b = getBitString(k, l);
//		// повтор алгоритма P для первых l битов
//		if (j_ >= l)
//		{
//			initialize(root);
//			run(k, l);
//		}
//		//
//		Node *r = root + id;
//		//
//		q_->setXlinktag(qid_, r, 0);
//		//
//		r->setXlinktag(b, r, 1);
//		r->setXlinktag(1ul ^ b, p_, qtag_);
//		//
//		r->setSkip(l);
//	}
//};
////--------------------------------------------------------
//// BWT - соритровка
//// L - длина сортируемого буфера
//// dbuff - буфер длины 2*L, в первой половине данные
//// node - выделенная память для хранения узлов, размер L
//// в результате получается отсортированный буфер
//// возвращаемое начение - положение начального символа
//unsigned bwtSort(unsigned L, unsigned char *dbuff, Node *node)
//{
//	// копировать первую половину во вторую
//	std::copy(dbuff, dbuff + L, dbuff + L);
//	dbuff[2 * L - 1] = ~dbuff[2 * L - 1];
//	// создать корень
//	node->initializeRoot();
//	// цикл по байтам буфера
//	PatAddNodeBase::initAdd();
//	unsigned id;
//	for (id = 1; id != L / 2 + 1; ++id)
//	{
//		// добавить узел
//		const PatAddNode pan(L, node, dbuff, id);
//		if (!pan.isNewNode())
//			break;
//	}
//	if (id == L / 2 + 1)
//	{
//		for (; id != L; ++id)
//			const PatAddNodeFast pan(L, node, dbuff, id);
//	}
//	const unsigned mult = L / id;
//	id = 0;
//	unsigned zeroId = 0;
//	PatIterator pit(node);
//	do
//	{
//		pit.runLeft();
//		const unsigned offs = pit.getText(node);
//		if (offs == 0)
//			zeroId = id;
//		const unsigned char byte = dbuff[offs + L - 1];
//		for (unsigned id2 = 0; id2 != mult; ++id2)
//			dbuff[id++] = byte;
//	} while (pit.goRight());
//	return zeroId;
//}
////--------------------------------------------------------
//// обратное BWT - преобразование
//// L - длина десортируемого буфера
//// dbuff - буфер длины 2*L, в первой половине данные
//// pos - положение начального символа (передавать zeroId)
//// vect - выделенная память для хранения
//// вектора обратного преобразования, размер (0x100+L)
//// в результате получается отсортированный буфер
//// (во второй половине)
//void bwtUnsort(unsigned L, unsigned char *dbuff,
//	unsigned pos, unsigned *vect)
//{
//	unsigned *freq = vect;
//	vect += 0x100;
//	std::fill(freq, freq + 0x100, 0);
//	unsigned id;
//	for (id = 0; id != L; ++id)
//		++freq[dbuff[id]];
//	unsigned sum = 0;
//	for (id = 0; id != 0x100; ++id)
//		freq[id] = (sum += freq[id]) - freq[id];
//	for (id = 0; id != L; ++id)
//		vect[freq[dbuff[id]]++] = id;
//	for (id = 0; id != L; ++id)
//		dbuff[L + id] = dbuff[pos = vect[pos]];
//}
////--------------------------------------------------------
//inline unsigned readSize(const std::string &str)
//{
//	unsigned num = 0;
//	std::string::const_iterator it;
//	for (it = str.begin();
//		it != str.end() && '0' <= *it&&*it <= '9'; ++it)
//	{
//		num *= 10;
//		num += *it - '0';
//	}
//	if (it != str.end())
//	{
//		switch (*it)
//		{
//		case 'm':
//			num <<= 10;
//		case 'k':
//			num <<= 10;
//			break;
//		}
//	}
//	return num;
//}
////--------------------------------------------------------
//// главная функция
//int go2(int argc, char *argv[])
//{
//	const char copyRight[] =
//		"Burrows-Wheeler sorting program.";
//	const char helpStr[] =
//		"SORT <e|d> infile outfile [blockSize]\n"
//		"\tblockSize (encode only) like 1m == 1024k (default 2m)\n";
//	bool allCorrect = true, isDecode;
//	if (argc<4)
//		allCorrect = false;
//	else if (argv[1][1] == 0)
//	{
//		if (argv[1][0] == 'e' || argv[1][0] == 'E')
//			isDecode = false;
//		else if (argv[1][0] == 'd' || argv[1][0] == 'D')
//			isDecode = true;
//		else
//			allCorrect = false;
//	}
//	else
//		allCorrect = false;
//	std::cout << copyRight << std::endl;
//	if (allCorrect)
//	{
//		HANDLE inh = ::CreateFile(argv[2], GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, 0);
//		HANDLE outh = ::CreateFile(argv[3], GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, 0);
//		if (inh == INVALID_HANDLE_VALUE || outh == INVALID_HANDLE_VALUE)
//		{
//			std::cerr << "File create error!" << std::endl;
//			return 1;
//		}
//		unsigned long stub;
//		unsigned blockSize = 2 << 20;
//		unsigned long realSize;
//		double secs = 0.;
//		if (isDecode)
//		{
//			// unsort
//			blockSize = 0;
//			std::cout << "Unsort...";
//			//
//			unsigned char *dbuff = 0;
//			unsigned *vect = 0;
//			for (;;)
//			{
//				::ReadFile(inh, &realSize, sizeof(realSize), &stub, 0);
//				if (!stub)
//					break;
//				if (sizeof(realSize) != stub)
//				{
//					std::cerr << "Defect in input" << std::endl;
//					return 2;
//				}
//				if (realSize>blockSize)
//				{
//					if (blockSize)
//					{
//						::VirtualFree(vect, 0, MEM_RELEASE);
//						::VirtualFree(dbuff, 0, MEM_RELEASE);
//					}
//					dbuff = static_cast<unsigned char*>(
//						::VirtualAlloc(0, 2 * realSize,
//							MEM_COMMIT, PAGE_READWRITE));
//					vect = static_cast<unsigned*>(
//						::VirtualAlloc(0,
//						(0x100 + realSize) * sizeof(unsigned),
//							MEM_COMMIT, PAGE_READWRITE));
//					blockSize = realSize;
//				}
//				unsigned zeroId;
//				::ReadFile(inh, &zeroId, sizeof(zeroId), &stub, 0);
//				if (sizeof(zeroId) != stub)
//				{
//					std::cerr << "Defect in input" << std::endl;
//					return 2;
//				}
//				::ReadFile(inh, dbuff, realSize, &stub, 0);
//				if (realSize != stub)
//				{
//					std::cerr << "Defect in input" << std::endl;
//					return 2;
//				}
//				bwtUnsort(realSize, dbuff, zeroId, vect);
//				::WriteFile(outh, dbuff + realSize, realSize, &stub, 0);
//			}
//			if (blockSize)
//			{
//				::VirtualFree(vect, 0, MEM_RELEASE);
//				::VirtualFree(dbuff, 0, MEM_RELEASE);
//			}
//			//
//		}
//		else
//		{
//			// sort
//			if (argv[4])
//				blockSize = readSize(argv[4]);
//			std::cout << "Sort using " << blockSize << " block size...";
//			//
//			unsigned char *dbuff = static_cast<unsigned char*>(
//				::VirtualAlloc(0, 2 * blockSize, MEM_COMMIT,
//					PAGE_READWRITE));
//			Node *node = static_cast<Node*>(
//				::VirtualAlloc(0, blockSize * sizeof(Node),
//					MEM_COMMIT, PAGE_READWRITE));
//			do
//			{
//				::ReadFile(inh, dbuff, blockSize, &realSize, 0);
//				if (realSize)
//				{
//					
//					const unsigned zeroId = bwtSort(realSize, dbuff, node);
//					
//					
//					::WriteFile(outh, &realSize, sizeof(realSize), &stub, 0);
//					::WriteFile(outh, &zeroId, sizeof(zeroId), &stub, 0);
//					::WriteFile(outh, dbuff, realSize, &stub, 0);
//				}
//			} while (realSize == blockSize);
//			::VirtualFree(dbuff, 0, MEM_RELEASE);
//			::VirtualFree(node, 0, MEM_RELEASE);
//			//
//		}
//		::CloseHandle(outh);
//		::CloseHandle(inh);
//		std::cout << ' ' << secs << " sec." << std::endl;
//	}
//	else
//		std::cout << helpStr;
//	return 0;
//}