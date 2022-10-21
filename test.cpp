#include "gtest/gtest.h"

#include "Board.h"

class BoardTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        board.setWidth(5);
        board.setHeight(5);
    }

    Board board;
};

TEST_F(BoardTest, BoardConstruct)
{
    EXPECT_EQ(5, board.width());
    EXPECT_EQ(5, board.height());
}

TEST_F(BoardTest, BoardPlaceToy)
{
    board.execCommand("PLACE 2, 3, NORTH");

    EXPECT_EQ(2, board.robot().x());
    EXPECT_EQ(3, board.robot().y());
    EXPECT_EQ(North, board.robot().direction());
}

TEST_F(BoardTest, BoardTurnLeftToy)
{
    board.execCommand("PLACE 2, 3, NORTH");
    board.execCommand("LEFT");

    EXPECT_EQ(2, board.robot().x());
    EXPECT_EQ(3, board.robot().y());
    EXPECT_EQ(West, board.robot().direction());
}

TEST_F(BoardTest, BoardTurnRightToy)
{
    board.execCommand("PLACE 2, 3, NORTH");
    board.execCommand("RIGHT");

    EXPECT_EQ(2, board.robot().x());
    EXPECT_EQ(3, board.robot().y());
    EXPECT_EQ(East, board.robot().direction());
}

TEST_F(BoardTest, BoardMoveToy1)
{
    board.execCommand("PLACE 2, 3, NORTH");
    board.execCommand("MOVE");

    EXPECT_EQ(2, board.robot().x());
    EXPECT_EQ(4, board.robot().y());

    board.execCommand("MOVE");
    EXPECT_EQ(4, board.robot().y());
}

TEST_F(BoardTest, BoardMoveToy2)
{
    board.execCommand("PLACE 0, 0, SOUTH");
    board.execCommand("MOVE");

    EXPECT_EQ(0, board.robot().x());
    EXPECT_EQ(0, board.robot().y());
}

TEST_F(BoardTest, BoardMoveToy3)
{
    board.execCommand("PLACE 1, 2, EAST");
    board.execCommand("MOVE");
    board.execCommand("RIGHT");
    board.execCommand("MOVE");
    board.execCommand("LEFT");
    board.execCommand("MOVE");
    board.execCommand("MOVE");
    EXPECT_EQ(4, board.robot().x());
    EXPECT_EQ(1, board.robot().y());
    EXPECT_EQ(East, board.robot().direction());

    board.execCommand("MOVE");
    board.execCommand("MOVE");
    EXPECT_EQ(4, board.robot().x());
    EXPECT_EQ(1, board.robot().y());
    EXPECT_EQ(East, board.robot().direction());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}