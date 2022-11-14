<?php

namespace App\Database\Migrations\API;

use CodeIgniter\Database\Migration;

class Detail extends Migration
{
    public function up()
    {
        $this->forge->addField([
            'id_detail' => [
                'type'           => 'INT',
                'constraint'     => 5,
                'unsigned'       => true,
                'auto_increment' => true
            ],
            'time' => [
                'type' => 'TIME',
                'null' => true
            ],
            'amount' => [
                'type' => 'INT',
                'null' => true
            ],
            'id_type' => [
                'type' => 'INT',
                'null' => false,
                'unsigned' => true
            ],
            'id_config' => [
                'type' => 'INT',
                'null' => false,
                'unsigned' => true
            ],
            'created_at' => [
                'type' => 'DATETIME',
                'null' => true
            ],
            'updated_at' => [
                'type' => 'DATETIME',
                'null' => true
            ],
            'deleted_at' => [
                'type' => 'DATETIME',
                'null' => true
            ],

        ]);
        $this->forge->addKey('id_detail', true);
        $this->forge->addForeignKey('id_type', 'type', 'id_type');
        $this->forge->addForeignKey('id_config', 'config', 'id_config');
        $this->forge->createTable('detail');
    }

    public function down()
    {
        $this->forge->dropTable('detail');
    }
}
