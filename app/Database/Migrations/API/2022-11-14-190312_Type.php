<?php

namespace App\Database\Migrations\API;

use CodeIgniter\Database\Migration;

class Type extends Migration
{
    public function up()
    {
        $this->forge->addField([
            'id_type' => [
                'type'           => 'INT',
                'constraint'     => 5,
                'unsigned'       => true,
                'auto_increment' => true
            ],
            'description' => [
                'type'       => 'VARCHAR',
                'constraint' => '50',
                'null'       => true
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
        $this->forge->addKey('id_type', true);
        $this->forge->createTable('type');
        //
    }

    public function down()
    {
        $this->forge->dropTable('type');
    }
}
